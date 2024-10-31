# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.17)

# Устанавливаем имя проекта
project(MyProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем путь к заголовочным файлам
include_directories(include)

# Добавляем исходные файлы
set(SOURCES
    main.cpp
    include/array.hpp
    include/concept.hpp
    include/figure.hpp
    include/point.hpp
    include/rectangle.hpp
    include/square.hpp
    include/triangle.hpp
)

# Добавляем исполняемый файл
add_executable(try ${SOURCES})

# Устанавливаем флаги компиляции (опционально)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Устанавливаем флаги линковки (опционально)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")