#pragma once
#include <iostream>
#include "../include/concept.hpp"
#include <concepts>


template <scalar_type T>
class point {
    public :
        T _x, _y;
        point();
        point(T x, T y);
        //virtual ~point() noexcept;

        bool operator==(const point<T>& p);
        // bool operator!=(const point& p);
        template<scalar_type C>
        friend std::istream& operator>>(std::istream& is, point<C>& point);
        friend std::ostream& operator<<(std::ostream& os, const point<C>& point);
};

template<scalar_type T>
point<T>::point() : _x(0), _y(0) {}

template<scalar_type T>
point<T>::point(T x, T y) : _x(x), _y(y) {}

template<scalar_type T>
bool point<T>::operator==(const point<T>& p) {
    return (this->_x == p._x && this->_y == p._y);
}

template<scalar_type T>
std::istream& operator>>(std::istream& is, point<T>& point) {
    std::cout << "Вводи координаты точки\n";
    is >> point._x >> point._y;
    return is;
}

template<scalar_type T>
std::ostream& operator<<(std::ostream& os, const point<T>& point) {
    os << "( " << point._x << ":" << point._y << " )\n";
    return os;
}