#pragma once
#include "../include/concept.hpp"
#include "../include/point.hpp"
#include "../include/figure.hpp"
#include <concepts>


template <scalar_type T>
class triangle : public figure<T>{
    public :
        triangle();
        triangle(const point<T>& x, const point<T>& y, const point<T>& z);

        triangle<T> &operator=(const triangle &other_triangle);
        triangle<T> &operator=(const triangle &&other_triangle) noexcept;

        //не хватало копирования и перемещения 
        triangle(const triangle<T> &other_triangle);
        triangle(const triangle<T> &&other_triangle);

        bool operator==(const figure<T> &other_triangle) const;

        void get_points_of_figure() const;
        point<T> get_center() const;
        operator double() const;

        //template <scalar_type C>
        friend std::istream& operator>>(std::istream& is, triangle& f) {
            point<T> coordinats[3];
            is >> coordinats[0] >> coordinats[1] >> coordinats[2];
            if (is.fail()) {
                throw std::invalid_argument("input fail");
            }
            f = triangle(coordinats[0], coordinats[1], coordinats[2]);
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const triangle& figure) {
            os << "coordinates of triangle\n";
            os << *figure.a << std::endl << *figure.b << std::endl << *figure.c << std::endl;
            return os;
        }

        bool valid_triangle() const;
    private : 
        std::unique_ptr<point<T>> a;
        std::unique_ptr<point<T>> b;
        std::unique_ptr<point<T>> c;
};

//Копирование 
template<scalar_type T>
triangle<T>::triangle(const triangle<T> &other_triangle) {
    if(this != &other_triangle) {
        a = std::make_unique<point<T>>(*other_triangle.a);
        b = std::make_unique<point<T>>(*other_triangle.b);
        c = std::make_unique<point<T>>(*other_triangle.c);
    }
    //return *this;
}

template<scalar_type T>
triangle<T>::triangle(const triangle<T> &&other_triangle) {
    if(this != &other_triangle) {
        a = std::move(*other_triangle.a);
        b = std::move(*other_triangle.b);
        c = std::move(*other_triangle.c);
    }
    //return *this;
}




template<scalar_type T>
static double distance(const point<T>& p1, const point<T>& p2) {
    return std::sqrt((p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y));
}

template<scalar_type T>
bool triangle<T>::valid_triangle() const { 
    double side_0_1 = distance(*a, *b);
    double side_1_2 = distance(*b, *c);
    double side_2_0 = distance(*c, *a);

    if(side_0_1 + side_1_2 > side_2_0 && side_1_2 + side_2_0 > side_0_1 && side_0_1 + side_2_0 > side_1_2) {
        return true;
    }
    else {
        throw std::invalid_argument("cannot build triangle from this points");
    }
}

template <scalar_type T>
triangle<T>::triangle(const point<T>& x, const point<T>& y, const point<T>& z) {
    a = std::make_unique<point<T>>(std::move(x));
    b = std::make_unique<point<T>>(std::move(y));
    c = std::make_unique<point<T>>(std::move(z));
    valid_triangle();
}

template<scalar_type T>
triangle<T> &triangle<T>::operator=(const triangle<T> &other_triangle) {
    if(this != &other_triangle) {
        a = std::make_unique<point<T>>(*other_triangle.a);
        b = std::make_unique<point<T>>(*other_triangle.b);
        c = std::make_unique<point<T>>(*other_triangle.c);
    }
    return *this;
}

template <scalar_type T>
triangle<T> &triangle<T>::operator=(const triangle &&other_triangle) noexcept{
    if(this != &other_triangle) {
        a = std::move(*other_triangle.a);
        b = std::move(*other_triangle.b);
        c = std::move(*other_triangle.c);
    }
    return *this;
}

template <scalar_type T>
bool triangle<T>::operator==(const figure<T> &other_triangle) const {
    const triangle* trey = dynamic_cast<const triangle*>(&other_triangle);
    if(!trey) {
        return false;
    }
    // if(*this->a == *other_triangle.a && *this->b == *other_triangle.b && *this->c == *other_triangle.c) {
    //     return true;
    // }
    if(*a == *trey->a && *b == *trey->b && *c == *trey->c) {
        return true;
    }
    return false;
    
}

template<scalar_type T>
void triangle<T>::get_points_of_figure() const{
    std::cout << *this << std::endl;
}

template<scalar_type T>
point<T> triangle<T>::get_center() const{
    // double x_centre = (*this->a._x + *this->b._x + *this->c._x) / 3;
    // double y_centre = (*this->a._y + *this->b._y + *this->c._y) / 3;
    double x_centre = (a->_x + b->_x + c->_x) / 3;
    double y_centre = (a->_y + b->_y + c->_y) / 3;
    return point<T>{x_centre, y_centre};
}

template <scalar_type T>
triangle<T>::operator double() const {
    double side1 = distance(*a, *b);
    double side2 = distance(*b, *c);
    double side3 = distance(*c, *a);
    double half_of_perimetr = (side1 + side2 + side3) / 2;
    return sqrt(half_of_perimetr * (half_of_perimetr - side1) * (half_of_perimetr - side2) * (half_of_perimetr - side3));
}

// template<scalar_type T>
// std::istream& operator>>(std::istream& is, triangle<T>& f) {
//     point<T> coordinats[3];
//     is >> coordinats[0] >> coordinats[1] >> coordinats[2];
//     if(is.fail()) {
//         throw std::invalid_argument("input fail");
//     }
//     this->a = std::make_unique<point<T>>(coordinats[0]);
//     this->b = std::make_unique<point<T>>(coordinats[1]);
//     this->c = std::make_unique<point<T>>(coordinats[2]);
//     return is;
// } 

// template<scalar_type T>
// std::ostream& operator<<(std::ostream& os, const triangle<T>& figure) {
//     os << "coordinates of triangle\n";
//     for(int i = 0; i < 3; ++i) {
//         os << figure.points[i];
//     }
//     os << *this->a << std::endl << *this->b << std::endl << *this->c << std::endl;
//     return os;
// }