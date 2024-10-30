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


        void add(const figure<T> &some_figure);
        bool remove_last();
        bool remove_all();
        size_t get_size() const;
        size_t get_capacity() const;
        //void print() const;
        T common_area() const;

        std::shared_ptr<figure<T>> operator[](size_t index) const;

    private :
        void resize();
        std::unique_ptr<std::shared_ptr<figure<T>>[]> figures;
        size_t capacity;
        size_t size;
};

template<scalar_type T>
array<T>::array() {
    capacity = default_capacity;
    size = default_size;
    figures = std::make_unique<figure<T>>[]>(capacity);
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
        new_figures[i] = figures[i];
    }
    delete[] figures;
    figures = new_figures;
    capacity *= 2;
}

template<scalar_type T>
void array<T>::add(const figure<T> &some_figure) {
    figures[size] = std::make_shared<figure<T>>(some_figure);
    ++size;
    if(10 * this->size >= 8 * this->capacity) {
        resize();
    }
}

template<scalar_type T>
bool array<T>::remove_last() {
    if(this->size == 0) {
        return false;
    }
    delete figures[--size];
    return true;
}

template<scalar_type T>
bool array<T>::remove_all() {
    if(this->size == 0) {
        return false;
    }
    for(int i = 0; i < size; ++i) {
        delete figures[i];
    }

    this->size = 0;
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

// template<scalar_type T>
// void array<T>::print() const {}

template<scalar_type T>
T array<T>::common_area() const {
    T all_space = 0;
    for(size_t i = 0; i < this->size; ++i) {
        all_space += static_cast<double>(*figures[i]);
    }

    return all_space;
}

template<scalar_type T>
std::shared_ptr<figure<T>> array<T>::operator[](size_t index) const {
    if(index >= this->size || index < 0) {
        throw std::out_of_range("index out oof range\n");
    }
    return array[index];
}
