/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** primitives.hpp
*/

#pragma once

#include "raytracer.hpp"
#include <iostream>

namespace RayTracer {
    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;

            virtual bool hits(const Ray &ray) const = 0;

            virtual void displayPrimitive() const = 0;
    };

    typedef struct RGB {
        int r;
        int g;
        int b;
    } RGB;

    class APrimitive : public IPrimitive {
        public:
            APrimitive() : _color({0, 0, 0}) {};
            APrimitive(RGB color) : _color(color) {};
            virtual ~APrimitive() = default;

            //* Getters
            RGB getColor() const {
                return _color;
            }

            //* Setters
            void setColor(RGB color) {
                _color = color;
            }

        protected:
            RGB _color;
    };

    class Sphere : public APrimitive {
        public:
            //* Attributes
            Math::Point3D _center;
            double _radius;

            //* Constructors
            Sphere() : _center(), _radius(0), APrimitive({0, 0, 0}) {}

            Sphere(const Math::Point3D &center, double radius, RGB color)
                : _center(center), _radius(radius), APrimitive(color) {}

            Sphere(const Sphere &s) : _center(s._center), _radius(s._radius), APrimitive(s._color) {}

            Sphere(Sphere &&s) : _center(s._center), _radius(s._radius), APrimitive(s._color) {
                s._center = Math::Point3D();
                s._radius = 0;
                s._color = {0, 0, 0};
            }

            //* Destructor
            ~Sphere() = default;

            //* Operators
            Sphere &operator=(const Sphere &s) {
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                    _color = s._color;
                }
                return *this;
            }

            Sphere &operator=(Sphere &&s) noexcept {
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                    _color = s._color;
                    s._center = Math::Point3D();
                    s._radius = 0;
                    s._color = {0, 0, 0};
                }
                return *this;
            }

            //* Methods
            bool hits(const Ray &ray) const {
                Math::Vector3D oc = ray.getOrigin() - _center;
                double a = ray.getDirection().dot(ray.getDirection());
                double b = 2.0 * oc.dot(ray.getDirection());
                double c = oc.dot(oc) - _radius * _radius;
                double discriminant = b * b - 4 * a * c;
                return (discriminant >= 0);
            }

            void displayPrimitive() const {
                std::cout << "[SPHERE]" << std::endl;
                std::cout << "Center : {" << _center.x << ", " << _center.y << ", " << _center.z << "}" << std::endl;
                std::cout << "Radius: " << _radius << std::endl;
                std::cout << "Color : {" << _color.r << ", " << _color.g << ", " << _color.b << "}" << std::endl;
            }

            //* Getters
            const Math::Point3D &getCenter() const {
                return _center;
            }

            double getRadius() const {
                return _radius;
            }

            //* Setters
            void setCenter(const Math::Point3D &center) {
                _center = center;
            }

            void setRadius(double radius) {
                _radius = radius;
            }
    };
}
