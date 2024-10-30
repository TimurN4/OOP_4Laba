#pragma once
#include "../include/concept.hpp"
#include "../include/point.hpp"
#include "../include/figure.hpp"
#include <concepts>


template <scalar_type T>
class square : public figure<T>{
    public :
        square();
        square(const point<T>& x, const point<T>& y, const point<T>& z, const point<T>& w);

        square<T> &operator=(const square &other_square);
        square<T> &operator=(const square &&other_square) noexcept;
        bool operator==(const figure<T> &other_square) const;

        void get_points_of_figure() const;
        point<T> get_center() const;
        operator double() const;

        template <scalar_type C>
        friend std::istream& operator>>(std::istream& is, square<C>& f);
        friend std::ostream& operator<<(std::ostream& os, const square<C>& figure);

        bool valid_triangle() const;
    private : 
        std::unique_ptr<point<T>> a;
        std::unique_ptr<point<T>> b;
        std::unique_ptr<point<T>> c;
        std::unique_ptr<point<T>> d;
};


template<scalar_type T>
static double distance1(const point<T>& p1, const point<T>& p2) {
    return std::sqrt((p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y));
}

template<scalar_type T>
bool square<T>::valid_triangle() const { // y = kx + b
    double side_0_1 = distance1(*a, *b);
    double side_1_2 = distance1(*b, *c);
    double side_2_3 = distance1(*c, *d);
    double side_3_0 = distance1(*a, *d);

    double side_0_2 = distance1(*a, *c);
    double side_1_3 = distance1(*b, *d);

    if(side_0_1 == side_1_2 && side_1_2 == side_2_3 && side_2_3 == side_3_0 && side_3_0 == side_0_1 && side_0_2 == side_1_3) {
        return true;
    }
    else {
        throw std::invalid_argument("not square");
    }
}

template <scalar_type T>
square<T>::square(const point<T>& x, const point<T>& y, const point<T>& z, const point<T>& w) {
    a = std::make_unique<point<T>>(std::move(x));
    b = std::make_unique<point<T>>(std::move(y));
    c = std::make_unique<point<T>>(std::move(z));
    d = std::make_unique<point<T>>(std::move(w));
    valid_square();
}

template<scalar_type T>
square<T> &square<T>::operator=(const square<T> &other_square) {
    if(this != other_square) {
        a = std::make_unique<point<T>>(*other_square.a);
        b = std::make_unique<point<T>>(*other_square.b);
        c = std::make_unique<point<T>>(*other_square.c);
        d = std::make_unique<point<T>>(*other_square.d);
    }
    return *this;
}

template <scalar_type T>
square<T> &square<T>::operator=(const square &&other_square) noexcept{
    if(this != other_square) {
        a = std::move(*other_square.a);
        b = std::move(*other_square.b);
        c = std::move(*other_square.c);
        d = std::move(*other_square.d);
    }
    return *this;
}

template <scalar_type T>
bool square<T>::operator==(const figure<T> &other_square) const {
    const square* trey = dynamic_cast<const square*>(&other_square);
    if(!trey) {
        return false;
    }
    if(*this->a == *other_square.a && *this->b == *other_square.b && *this->c == *other_square.c && *this->d = *other_square.d) {
        return true;
    }
    return false;
    
}

template<scalar_type T>
void square<T>::get_points_of_figure() const{
    std::cout << *this << std::endl;
}

template<scalar_type T>
point<T> square<T>::get_center() const{
    double x_centre = (*this->a._x + *this->c._x) / 2;
    double y_centre = (*this->a._y + *this->c._y) / 2;

    return point<T>{x_centre, y_centre};
}

template <scalar_type T>
square<T>::operator double() const {
    double storona1 = sqrt(pow(*this->a._x - *this->b._x, 2) + pow(*this->a._y - *this->b._y, 2));
    return storona1 * storona1;
}

template<scalar_type T>
std::istream& operator>>(std::istream& is, square<T>& f) {
    point<T> coordinats[4];
    is >> coordinats[0] >> coordinats[1] >> coordinats[2] >> coordinats[3];
    if(is.fail()) {
        throw std::invalid_argument("input fail");
    }
    this->a = std::make_unique<point<T>>(coordinats[0]);
    this->b = std::make_unique<point<T>>(coordinats[1]);
    this->c = std::make_unique<point<T>>(coordinats[2]);
    this->d = std::make_unique<point<T>>(coordinats[3]);
    return is;
}

template<scalar_type T>
std::ostream& operator<<(std::ostream& os, const square<T>& figure) {
    os << "coordinates of square\n";
    for(int i = 0; i < 4; ++i) {
        os << figure.points[i];
    }
    os << *this->a << std::endl << *this->b << std::endl << *this->c << std::endl << *this->d << std:: endl;
    return os;
}