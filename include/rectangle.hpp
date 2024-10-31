#pragma once
#include "../include/concept.hpp"
#include "../include/point.hpp"
#include "../include/figure.hpp"
#include <concepts>


template <scalar_type T>
class rectangle : public figure<T>{
    public :
        rectangle();
        rectangle(const point<T>& x, const point<T>& y, const point<T>& z, const point<T>& w);


        //rectangle &operator=(const rectangle &other_rectangle);
        //rectangle &operator=(const rectangle &&other_rectangle) noexcept;
        rectangle<T> &operator=(const rectangle &other_rectangle);
        rectangle<T> &operator=(const rectangle &&other_rectangle) noexcept;
        bool operator==(const figure<T> &other_rectangle) const;

        void get_points_of_figure() const;
        point<T> get_center() const;
        operator double() const;

        //template <scalar_type C>
        friend std::istream& operator>>(std::istream& is, rectangle& f) {
            point<T> coordinats[4];
            is >> coordinats[0] >> coordinats[1] >> coordinats[2] >> coordinats[3];
            if(is.fail()) {
                throw std::invalid_argument("input fail");
            }
            f = rectangle(coordinats[0], coordinats[1], coordinats[2], coordinats[3]);
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const rectangle& figure) {
            os << "coordinates of rectangle\n";
            os << *figure.a << std::endl << *figure.b << std::endl << *figure.c << std::endl << *figure.d << std:: endl;
            return os;
        }

        bool valid_rectangle() const;
    private : 
        std::unique_ptr<point<T>> a;
        std::unique_ptr<point<T>> b;
        std::unique_ptr<point<T>> c;
        std::unique_ptr<point<T>> d;
};


template<scalar_type T>
static double distance2(const point<T>& p1, const point<T>& p2) {
    return std::sqrt((p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y));
}

template<scalar_type T>
bool rectangle<T>::valid_rectangle() const { // y = kx + b
    double side_0_1 = distance2(*a, *b);
    double side_1_2 = distance2(*b, *c);
    double side_2_3 = distance2(*c, *d);
    double side_3_0 = distance2(*a, *d);

    double side_0_2 = distance2(*a, *c);
    double side_1_3 = distance2(*b, *d);

    if(side_0_1 == side_2_3 && side_1_2 == side_3_0 && side_0_2 == side_1_3) {
        return true;
    }
    else {
        throw std::invalid_argument("not rectangle");
    }
}

template <scalar_type T>
rectangle<T>::rectangle(const point<T>& x, const point<T>& y, const point<T>& z, const point<T>& w) {
    a = std::make_unique<point<T>>(std::move(x));
    b = std::make_unique<point<T>>(std::move(y));
    c = std::make_unique<point<T>>(std::move(z));
    d = std::make_unique<point<T>>(std::move(w));
    valid_rectangle();
}

template<scalar_type T>
rectangle<T> &rectangle<T>::operator=(const rectangle<T> &other_rectangle) {
    if(this != other_rectangle) {
        a = std::make_unique<point<T>>(*other_rectangle.a);
        b = std::make_unique<point<T>>(*other_rectangle.b);
        c = std::make_unique<point<T>>(*other_rectangle.c);
        d = std::make_unique<point<T>>(*other_rectangle.d);
    }
    return *this;
}

template <scalar_type T>
rectangle<T> &rectangle<T>::operator=(const rectangle &&other_rectangle) noexcept{
    if(this != other_rectangle) {
        a = std::move(*other_rectangle.a);
        b = std::move(*other_rectangle.b);
        c = std::move(*other_rectangle.c);
        d = std::move(*other_rectangle.d);
    }
    return *this;
}

template <scalar_type T>
bool rectangle<T>::operator==(const figure<T> &other_rectangle) const {
    const rectangle* trey = dynamic_cast<const rectangle*>(&other_rectangle);
    if(!trey) {
        return false;
    }
    if(*a == *other_rectangle.a && *b == *other_rectangle.b && *c == *other_rectangle.c && *d = *other_rectangle.d) {
        return true;
    }
    return false;
    
}

template<scalar_type T>
void rectangle<T>::get_points_of_figure() const{
    std::cout << *this << std::endl;
}

template<scalar_type T>
point<T> rectangle<T>::get_center() const{
    double x_centre = (a->_x + c->_x) / 2;
    double y_centre = (a->_y + c->_y) / 2;

    return point<T>{x_centre, y_centre};
}

template <scalar_type T>
rectangle<T>::operator double() const {
    double storona1 = sqrt(pow(a->_x - b->_x, 2) + pow(a->_y - b->_y, 2));
    double storona2 = sqrt(pow(b->_x - c->_x, 2) + pow(b->_y - c->_y, 2));
    return storona1 * storona2;
}

// template<scalar_type T>
// std::istream& operator>>(std::istream& is, rectangle<T>& f) {
//     point<T> coordinats[4];
//     is >> coordinats[0] >> coordinats[1] >> coordinats[2] >> coordinats[3];
//     if(is.fail()) {
//         throw std::invalid_argument("input fail");
//     }
//     a = std::make_unique<point<T>>(coordinats[0]);
//     b = std::make_unique<point<T>>(coordinats[1]);
//     c = std::make_unique<point<T>>(coordinats[2]);
//     d = std::make_unique<point<T>>(coordinats[3]);
//     return is;
// }

// template<scalar_type T>
// std::ostream& operator<<(std::ostream& os, const rectangle<T>& figure) {
//     os << "coordinates of rectangle\n";
//     for(int i = 0; i < 4; ++i) {
//         os << figure.points[i];
//     }
//     os << *a << std::endl << *b << std::endl << *c << std::endl << *d << std:: endl;
//     return os;
// }