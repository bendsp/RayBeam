/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** raytracer.hpp
*/

#pragma once

#include "math.hpp"

class Core;

namespace RayTracer {
    class Ray {
        public:
            //* Attributes
            Math::Point3D _origin;
            Math::Vector3D _direction;

            //* Constructors
            Ray() : _origin(), _direction() {}

            Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
                : _origin(origin), _direction(direction.normalized()) {}

            Ray(const Ray &r)
                : _origin(r._origin), _direction(r._direction.normalized()) {}

            Ray(Ray &&r) : _origin(r._origin), _direction(r._direction.normalized()) {
                r._origin = Math::Point3D();
                r._direction = Math::Vector3D();
            }

            //* Destructor
            ~Ray() = default;

            //* Operators
            Ray &operator=(const Ray &r) {
                if (this != &r) {
                    _origin = r._origin;
                    _direction = r._direction.normalized();
                }
                return *this;
            }

            Ray &operator=(Ray &&r) noexcept {
                if (this != &r) {
                    _origin = r._origin;
                    _direction = r._direction.normalized();
                    r._origin = Math::Point3D();
                    r._direction = Math::Vector3D();
                }
                return *this;
            }

            //* Getters
            const Math::Point3D &getOrigin() const {
                return _origin;
            }

            const Math::Vector3D &getDirection() const {
                return _direction;
            }

            //* Setters
            void setOrigin(const Math::Point3D &origin) {
                _origin = origin;
            }

            void setDirection(const Math::Vector3D &direction) {
                _direction = direction.normalized();
            }
    };

    class Camera {
        public:
            //* Attributes
            Math::Point3D _origin;
            Math::Rectangle3D _screen;
            int _width;
            int _height;
            double _fov; // TODO: add theses variables in the constructor

            //* Constructors
            Camera() : _origin(0, 0, 0), _screen() {}

            Camera(const Math::Point3D &origin, const Math::Rectangle3D &screen)
                : _origin(origin), _screen(screen) {}

            Camera(const Camera &c)
                : _origin(c._origin), _screen(c._screen) {}

            Camera(Camera &&c) : _origin(c._origin), _screen(c._screen) {
                c._origin = Math::Point3D();
                c._screen = Math::Rectangle3D();
            }

            //* Destructor
            ~Camera() = default;

            //* Operators
            Camera &operator=(const Camera &c) {
                if (this != &c) {
                    _origin = c._origin;
                    _screen = c._screen;
                }
                return *this;
            }

            Camera &operator=(Camera &&c) noexcept {
                if (this != &c) {
                    _origin = c._origin;
                    _screen = c._screen;
                    c._origin = Math::Point3D();
                    c._screen = Math::Rectangle3D();
                }
                return *this;
            }

            //* Methods
            RayTracer::Ray ray(double u, double v) const {
                Math::Point3D pOnScreen = _screen.pointAt(u, v);
                Math::Vector3D direction = pOnScreen - _origin;
                return RayTracer::Ray(_origin, direction);
            }

            //* Getters
            const Math::Point3D &getOrigin() const {
                return _origin;
            }

            const Math::Rectangle3D &getScreen() const {
                return _screen;
            }

            const int &getWidth() const {
                return _width;
            }

            const int &getHeight() const {
                return _height;
            }

            const double &getFov() const {
                return _fov;
            }

            //* Setters
            void setOrigin(const Math::Point3D &origin) {
                _origin = origin;
            }

            void setScreen(const Math::Rectangle3D &screen) {
                _screen = screen;
            }

            void setWidth(const int &width) {
                _width = width;
            }

            void setHeight(const int &height) {
                _height = height;
            }

            void setFov(const double &fov) {
                _fov = fov;
            }
    };
}

int parseFile(char *filepath, Core *core);
