/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** core.hpp
*/

#pragma once

#include <libconfig.h++>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "primitives.hpp"
#include "lights.hpp"
#include "math.hpp"
#include <vector>

class Core {
    public:
        // * Getters
        const RayTracer::Camera &getCamera() {
            return _camera;
        }
        const std::vector <RayTracer::IPrimitive *> &getPrimitives() {
            return _primitives;
        }
        const std::vector <RayTracer::ILight *> &getLights() {
            return _lights;
        }
        const double getAmbient() {
            return _ambient;
        }
        const double getDiffuse() {
            return _diffuse;
        }

        // * Setters / Adders
        void setCamera(const RayTracer::Camera &camera) {
            _camera = camera;
        }
        void addPrimitive(RayTracer::IPrimitive *primitive) {
            _primitives.push_back(primitive);
        }
        void addLight(RayTracer::ILight *light) {
            _lights.push_back(light);
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

        // * Attributes
        RayTracer::Camera _camera;
        std::vector <RayTracer::IPrimitive *> _primitives;
        std::vector <RayTracer::ILight *> _lights;
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