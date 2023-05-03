/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** core.hpp
*/

#pragma once

#include "raytracer.hpp"
#include "primitives.hpp"
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
        // * Setters / Adders
        void setCamera(const RayTracer::Camera &camera) {
            _camera = camera;
        }
        void addPrimitive(RayTracer::IPrimitive *primitive) {
            _primitives.push_back(primitive);
        }
        // * Attributes
    protected:
        RayTracer::Camera _camera;
        std::vector <RayTracer::IPrimitive *> _primitives;
};