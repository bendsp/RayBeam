#pragma once

#include <libconfig.h++>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include "primitives.hpp"
#include "lights.hpp"
#include "math.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Core {
    public:
        Core() : _ambient(0), _diffuse(0) {}

        // * Getters
        const RayTracer::Camera &getCamera() {
            return _camera;
        }
        const std::vector <std::unique_ptr<RayTracer::IPrimitive>> &getPrimitives() {
            return _primitives;
        }
        const std::vector <std::unique_ptr<RayTracer::ILight>> &getLights() {
            return _lights;
        }
        double getAmbient() {
            return _ambient;
        }
        double getDiffuse() {
            return _diffuse;
        }

        // * Setters / Adders
        void setCamera(const RayTracer::Camera &camera) {
            _camera = camera;
        }
        void addPrimitive(std::unique_ptr<RayTracer::IPrimitive> primitive) {
            _primitives.push_back(std::move(primitive));
        }
        void addLight(std::unique_ptr<RayTracer::ILight> light) {
            _lights.push_back(std::move(light));
        }
        void setAmbient(double ambient) {
            _ambient = ambient;
        }
        void setDiffuse(double diffuse) {
            _diffuse = diffuse;
        }

        // * Methods
        void displayScene(void);
        RayTracer::RGB castCameraRay(RayTracer::Ray ray);
        RayTracer::RGB castLightingRay(RayTracer::RGB materialColor, Math::HitPoint objectHitpoint);
        void printCoreInfo(void);
        void renderScene(sf::RenderWindow &window, sf::Texture &texture, sf::Sprite &sprite, sf::Uint8* pixels);

        // * Attributes
        RayTracer::Camera _camera;
        std::vector <std::unique_ptr<RayTracer::IPrimitive>> _primitives;
        std::vector <std::unique_ptr<RayTracer::ILight>> _lights;
        double _ambient;
        double _diffuse;

        //* Exception
        class CoreException : public std::exception {
            public:
                CoreException(std::string const &message) : _message(message) {};
                virtual ~CoreException() throw() {};
                virtual const char *what() const throw() {
                    return _message.c_str();
                };
            private:
                std::string _message;
        };
};

void parseCamera(const libconfig::Setting &root, Core *core);
void parsePrimitives(const libconfig::Setting &root, Core *core);
void parseLights(const libconfig::Setting &root, Core *core);
void parseTransformations(const libconfig::Setting &root, Core *core);
