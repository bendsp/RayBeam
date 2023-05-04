/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** core.hpp
*/

#pragma once

#include "primitives.hpp"
#include "lights.hpp"
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
        void display_scene(void);
        RayTracer::RGB checkColisions(RayTracer::Ray ray);
        // * Attributes
        RayTracer::Camera _camera;
        std::vector <RayTracer::IPrimitive *> _primitives;
        std::vector <RayTracer::ILight *> _lights;
};