/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** lights.hpp
*/

#pragma once

#include "math.hpp"

class Core;

namespace RayTracer {
    class ILight {
        public:
            ILight() = default;
            virtual ~ILight() = default;
            virtual float getBrightness() const = 0;
            virtual void setBrightness(float brightness) = 0;
            virtual double getIntensity(const Math::Point3D &point) const = 0;
    };
}