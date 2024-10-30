#pragma once
#include "../include/point.hpp"
#include "../include/concept.hpp"
#include "iostream"
#include "cmath"
#include <concepts>


template <scalar_type T>
class figure {
    public :
        virtual void get_points_of_figure() const = 0;
        virtual point<T> get_center() const = 0;
        virtual operator double() const = 0;

        virtual bool operator==(const figure& f) const = 0;// figure<T>
        template<scalar_type C>
        friend std::istream& operator>>(std::istream& is, figure<C>& f);
        friend std::ostream& operator<<(std::ostream& os, const figure<C>& figure);

        virtual ~figure() noexcept = default;
};