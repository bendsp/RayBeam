#include "core.hpp"
#include "primitives.hpp"
#include "raytracer.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

static int failures = 0;

static void expect(bool condition, const std::string &message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << std::endl;
        ++failures;
    }
}

static void testSphereHitInFront()
{
    RayTracer::Sphere sphere({0, 0, 5}, 1, {255, 0, 0});
    RayTracer::Ray ray({0, 0, 0}, {0, 0, 1});
    Math::HitPoint hit = sphere.hits(ray);

    expect(hit.hit, "sphere in front should be hit");
    expect(hit.distance > 0, "sphere hit distance should be positive");
    expect(std::abs(hit.distance - 4.0) < 0.001, "sphere hit should choose nearest positive distance");
}

static void testSphereBehindCamera()
{
    RayTracer::Sphere sphere({0, 0, -5}, 1, {255, 0, 0});
    RayTracer::Ray ray({0, 0, 0}, {0, 0, 1});

    expect(!sphere.hits(ray).hit, "sphere behind camera should not be hit");
    expect(std::isinf(sphere.getIntersectionDistance(ray)), "sphere behind camera should return infinite distance");
}

static void testSphereMiss()
{
    RayTracer::Sphere sphere({5, 0, 5}, 1, {255, 0, 0});
    RayTracer::Ray ray({0, 0, 0}, {0, 0, 1});

    expect(!sphere.hits(ray).hit, "missed sphere should not be hit");
    expect(std::isinf(sphere.getIntersectionDistance(ray)), "missed sphere should return infinite distance");
}

static void testColorClamping()
{
    Core core;
    core.setAmbient(2.0);
    RayTracer::RGB color = core.castLightingRay({200, -10, 300}, {true, 1, {0, 0, 0}});

    expect(color.r == 255, "red channel should clamp high values");
    expect(color.g == 0, "green channel should clamp low values");
    expect(color.b == 255, "blue channel should clamp high values");
}

static void testPrimaryRayUsesNearestHitDistance()
{
    Core core;
    core.setAmbient(1.0);
    core.addPrimitive(std::make_unique<RayTracer::Sphere>(Math::Point3D(0, 0, 8), 1, RayTracer::RGB{255, 0, 0}));
    core.addPrimitive(std::make_unique<RayTracer::Sphere>(Math::Point3D(0, 0, 5), 1, RayTracer::RGB{0, 255, 0}));

    RayTracer::RGB color = core.castCameraRay({{0, 0, 0}, {0, 0, 1}});

    expect(color.r == 0, "primary ray should not choose farther red sphere");
    expect(color.g == 255, "primary ray should choose nearest green sphere");
    expect(color.b == 0, "primary ray nearest hit blue channel should match object color");
}

static void testBinaryPpmExport()
{
    Core core;
    std::string path = "/tmp/raybeam_export_test.ppm";
    std::vector<sf::Uint8> pixels = {
        255, 0, 0, 255,
        0, 128, 255, 255
    };

    core.exportPpm(path, pixels.data(), 2, 1);

    std::ifstream file(path, std::ios::binary);
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::string header = "P6\n2 1\n255\n";

    expect(contents.rfind(header, 0) == 0, "binary PPM should have a P6 header");
    expect(contents.size() == header.size() + 6, "binary PPM should write exactly 3 bytes per pixel");
    expect(static_cast<unsigned char>(contents[header.size() + 0]) == 255, "binary PPM should preserve red byte");
    expect(static_cast<unsigned char>(contents[header.size() + 4]) == 128, "binary PPM should preserve green byte");
    expect(static_cast<unsigned char>(contents[header.size() + 5]) == 255, "binary PPM should preserve blue byte");
}

static void testParserMissingRequiredCameraField()
{
    std::string path = "/tmp/raybeam_missing_camera_field.cfg";
    std::ofstream file(path);

    file << "camera : { resolution = { width = 10; height = 10; }; fieldOfView = 72.0; };\n";
    file << "primitives : { spheres = (); };\n";
    file << "lights : { ambient = 0.4; diffuse = 0.6; point = (); directional = (); };\n";
    file.close();

    Core core;
    try {
        parseFile(path.data(), &core);
        expect(false, "parser should throw when a required camera field is missing");
    } catch (const Core::CoreException &exception) {
        std::string message = exception.what();
        expect(message.find("Missing required setting") != std::string::npos, "parser error should name missing required settings");
    }
}

int main()
{
    testSphereHitInFront();
    testSphereBehindCamera();
    testSphereMiss();
    testColorClamping();
    testPrimaryRayUsesNearestHitDistance();
    testBinaryPpmExport();
    testParserMissingRequiredCameraField();

    if (failures != 0)
        return 1;
    std::cout << "All tests passed" << std::endl;
    return 0;
}
