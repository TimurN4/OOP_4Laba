#include <iostream>
#include "./include/concept.hpp"
#include "./include/point.hpp"
#include "./include/array.hpp"
#include "./include/triangle.hpp"
#include "./include/square.hpp"
#include "./include/rectangle.hpp"
#include <string>
#include <concepts>


int main()
{
    array<double> arr(4);
    std::cout << arr.get_capacity() << std::endl;
    std::cout << arr.get_size() << std::endl;
    std::cout << arr.common_area() << std::endl;

    std::cout << "-------------------------------" << std:: endl;

    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    triangle<double> tmp(p1, p2, p3);
    auto t = std::make_shared<triangle<double>>(tmp);
    arr.add(t);

    std::cout << arr.get_capacity() << std::endl;
    std::cout << arr.get_size() << std::endl;
    std::cout << arr.common_area() << std::endl;
    std::cout << "-------------------------------" << std:: endl;


    // triangle<double> tmp1(p1, p2, p3);
    // auto r = std::make_shared<triangle<double>>(tmp1);
    // arr.add(r);

    // std::cout << "--------------------------------" << std::endl;

    // arr.print();

    bool rfr = arr.remove_last();
    std::cout << rfr << std::endl;
    std::cout << arr.get_capacity() << std::endl;
    std::cout << arr.get_size() << std::endl;
    std::cout << arr.common_area() << std::endl;


    // std::cout << double(tmp) << std::endl << tmp.get_center(); //<< std::endl << tmp.get_points_of_figure();
    // tmp.get_points_of_figure();
    //arr.add(tmp);
    // std::cout << arr.get_capacity() << std::endl;
    // std::cout << arr.get_size() << std::endl;
    // std::cout << arr.common_area() << std::endl;
    // arr.remove_last();
    // std::cout << arr.get_size() << std::endl;
    return 0;
}