#pragma once
#include <memory>
#include "../include/concept.hpp"
#include "../include/point.hpp"
#include "../include/figure.hpp"
#include "../include/triangle.hpp"
#include "../include/square.hpp"
#include "../include/rectangle.hpp"
#include <concepts>


template <scalar_type T>
class array {
        static const size_t default_capacity = 4;
        static const size_t default_size = 0;
    public :
        array();
        array(const size_t& n);
        ~array();

        //было
        //void add(const figure<T> &some_figure);
        //стало
        void add(std::shared_ptr<figure<T>> some_figure);

        bool remove_last();
        bool remove_index(const size_t &index);
        size_t get_size() const;
        size_t get_capacity() const;

        void print() const;

        T common_area() const;

        std::shared_ptr<figure<T>> &operator[](size_t index) const;

    private :
        void resize();
        std::unique_ptr<std::shared_ptr<figure<T>>[]> figures;
        size_t capacity;
        size_t size;
};

template<scalar_type T>
array<T>::~array() = default;

template<scalar_type T>
array<T>::array() {
    capacity = default_capacity;
    size = default_size;
    figures = std::make_unique<std::shared_ptr<figure<T>>[]>(capacity);
}

template<scalar_type T>
array<T>::array(const size_t& n) {
    capacity = n;
    size = default_size;
    figures = std::make_unique<std::shared_ptr<figure<T>>[]>(capacity);
}

template<scalar_type T>
void array<T>::resize() {
    std::unique_ptr<std::shared_ptr<figure<T>>[]> new_figures = std::make_unique<std::shared_ptr<figure<T>>[]>(capacity * 2);
    for(size_t i = 0; i < size; ++i) {
        new_figures[i] = std::move(figures[i]);
    }

    figures = std::move(new_figures);
    capacity *= 2;
}

template<scalar_type T>
void array<T>::add(std::shared_ptr<figure<T>> some_figure) {
    //Было
    //figures[size] = std::make_shared<figure<T>>(some_figure);
    //сейчас
    figures[size] = std::move(some_figure);
    ++size;
    if(10 * this->size >= 8 * this->capacity) {
        resize();
    }
}

template<scalar_type T>
bool array<T>::remove_last() {/////////////////////////////////////////////
    if(this->size == 0) {
        return false;
    }
    //Было
    //delete figures[--size];
    //сейчас 
    figures[size - 1].reset();
    size--;
    return true;
}

template<scalar_type T>
bool array<T>::remove_index(const size_t &index) {
    if(this->size == 0) {
        return false;
    }
    
    if(index < 0 || index >= capacity) {
        throw std::out_of_range("index is out of range\n");
    }

    for(size_t i = index; i < size - 1; ++i) {
        figures[i] = std::move(figures[i + 1]);
    }
    figures[size - 1].reset();
    --size;
    return true;
}

template<scalar_type T>
size_t array<T>::get_size() const {
    return this->size;
}

template<scalar_type T>
size_t array<T>::get_capacity() const {
    return this->capacity;
}

template<scalar_type T>
void array<T>::print() const {
    for(int i = 0; i < size; ++i) {
        std::cout << "info about " << i << " figure" << std::endl;
        std::cout << "area\n";
        std::cout << double(*figures[i]) << std::endl;
        std::cout << "geometric centre\n";
        std::cout << figures[i]->get_center() << std::endl;
        std::cout << "coordinats of figure\n";
        figures[i]->get_points_of_figure();
        std::cout << "---------------------------\n";
    }
}

template<scalar_type T>
T array<T>::common_area() const {
    T all_space = 0;
    for(size_t i = 0; i < this->size; ++i) {
        all_space += static_cast<double>(*figures[i]); //try to use double(*figures[i])
    }

    return all_space;
}

template<scalar_type T>
std::shared_ptr<figure<T>> &array<T>::operator[](size_t index) const {
    if(index >= this->size || index < 0) {
        throw std::out_of_range("index out oof range\n");
    }
    return figures[index];
}
