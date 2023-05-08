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

        // * Methods
        void displayScene(void);
        RayTracer::RGB checkColisions(RayTracer::Ray ray);

        // * Attributes
        RayTracer::Camera _camera;
        std::vector <RayTracer::IPrimitive *> _primitives;
        std::vector <RayTracer::ILight *> _lights;

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

void parsePrimitives(const libconfig::Setting &root, Core *core);
void parseLights(const libconfig::Setting &root, Core *core);
