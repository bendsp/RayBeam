/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** displayScene.cpp
*/

#include "core.hpp"
#include "raytracer.hpp"
#include "primitives.hpp"
#include "math.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

static int clampColor(int value)
{
    return std::clamp(value, 0, 255);
}

RayTracer::RGB Core::castLightingRay(RayTracer::RGB materialColor, Math::HitPoint objectHitpoint)
{
    double intensity = _ambient;
    RayTracer::Ray shadowRay;
    Math::HitPoint shadowHitpoint;

    for (size_t i = 0; i < _lights.size(); ++i) {
        bool illuminated = true;
        Math::Vector3D toLight = _lights[i]->getPosition() - objectHitpoint.hitPointVar;
        double lightDistance = toLight.magnitude();

        shadowRay = RayTracer::Ray(objectHitpoint.hitPointVar, toLight);
        for (size_t j = 0; j < _primitives.size(); ++j) {
            shadowHitpoint = _primitives[j]->hits(shadowRay);
            if (shadowHitpoint.hit == false) {
                continue;
            }
            if (abs(shadowHitpoint.distance) < 0.001) {
                continue;
            }
            if (shadowHitpoint.distance < lightDistance) {
                illuminated = false;
                break;
            }
        }
        if (illuminated) {
            intensity += _lights[i]->getIntensity(objectHitpoint.hitPointVar);
        }
    }
    int ar = clampColor(static_cast<int>(materialColor.r * intensity));
    int ag = clampColor(static_cast<int>(materialColor.g * intensity));
    int ab = clampColor(static_cast<int>(materialColor.b * intensity));
    RayTracer::RGB color = {ar, ag, ab};
    return color;
}

RayTracer::RGB Core::castCameraRay(RayTracer::Ray ray)
{
    float distance;
    float bestDistance = std::numeric_limits<float>::max();
    RayTracer::RGB color{0, 0, 0};
    Math::HitPoint hitPoint = Math::HitPoint();
    Math::HitPoint bestHitPoint = Math::HitPoint();
    for (size_t i = 0; i < _primitives.size(); i++) {
        if (hitPoint = _primitives[i]->hits(ray); hitPoint.hit) {
            // printf("hit\n");
            distance = _primitives[i]->getIntersectionDistance(ray);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestHitPoint = hitPoint;
                color = _primitives[i]->getColor();
            }
        }
    }
    color = castLightingRay(color, bestHitPoint);
    return color;
}

void Core::renderScene(sf::RenderWindow &window, sf::Texture &texture, sf::Sprite &sprite, sf::Uint8* pixels) {
    int width = _camera._width;
    int height = _camera._height;
    double aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    double width3D = 2 * _camera.getDistanceToScreen() * tan(0.5 * _camera.getFov());
    double height3D = width3D / (aspectRatio);
    Math::Vector3D right_vector = _camera.getRight();
    Math::Vector3D up_vector = _camera.getUp();
    Math::Vector3D horizontal_step = _camera.getRight() * (width3D / (width - 1));
    Math::Vector3D vertical_step = _camera.getUp() * (height3D / (height - 1));
    Math::Vector3D rayDirection;
    Math::Point3D camera_origin = _camera.getOrigin();
    Math::Point3D screen_center = _camera.getScreenCenter();
    Math::Point3D current_point;
    RayTracer::Ray current_ray;
    RayTracer::RGB color;

    std::ofstream outFile("output.ppm");

    outFile << "P3\n" << width << " " << height << "\n255\n";
    for (int y = height - 1; y >= 0;--y) {
        for (int x = width - 1; x >= 0; --x) {
            double fx = static_cast<double>(x);
            double fy = static_cast<double>(y);
            current_point = screen_center - (right_vector * (0.5 * width3D)) + (horizontal_step * fx) + (up_vector * (0.5 * height3D)) - (vertical_step * fy);
            rayDirection = (current_point - camera_origin).normalized();
            current_ray = RayTracer::Ray(camera_origin, rayDirection);
            color = castCameraRay(current_ray);
            int ir = clampColor(static_cast<int>(color.r));
            int ig = clampColor(static_cast<int>(color.g));
            int ib = clampColor(static_cast<int>(color.b));

            outFile << ir << " " << ig << " " << ib << "\n";

            int index = ((height - 1 - y) * width + (width - 1 - x)) * 4;
            pixels[index + 0] = ir;
            pixels[index + 1] = ig;
            pixels[index + 2] = ib;
            pixels[index + 3] = 255;
        }

        texture.update(pixels);
        sprite.setTexture(texture);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    outFile.close();
}

void Core::displayScene(void) {
    sf::RenderWindow window(sf::VideoMode(_camera._width, _camera._height), "Raytracer Output");
    sf::Texture texture;
    texture.create(_camera._width, _camera._height);
    sf::Sprite sprite;

    sf::Uint8* pixels = new sf::Uint8[_camera._width * _camera._height * 4];

    renderScene(window, texture, sprite, pixels);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Left) {
                        _camera.moveLeft(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        _camera.moveRight(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    else if (event.key.code == sf::Keyboard::Up) {
                        _camera.moveUp(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        _camera.moveDown(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    else if (event.key.code == sf::Keyboard::Z) {
                        _camera.moveForward(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    else if (event.key.code == sf::Keyboard::S) {
                        _camera.moveBackward(10);
                        renderScene(window, texture, sprite, pixels);
                    }
                    break;
            }
        }
    }
    delete[] pixels;
}
