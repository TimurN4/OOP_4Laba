# # Устанавливаем минимальную версию CMake
# cmake_minimum_required(VERSION 3.17)

# # Устанавливаем имя проекта
# project(MyProject)

# # Устанавливаем стандарт C++
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Добавляем путь к заголовочным файлам
# include_directories(include)

# # Добавляем исходные файлы
# set(SOURCES
#     main.cpp
#     include/array.hpp
#     include/concept.hpp
#     include/figure.hpp
#     include/point.hpp
#     include/rectangle.hpp
#     include/square.hpp
#     include/triangle.hpp
# )

# # Добавляем исполняемый файл
# add_executable(try ${SOURCES})

cmake_minimum_required(VERSION 3.14)

project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "include/*.hpp")

add_executable(MyProject main.cpp ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(MyProjectTests test/test.cpp ${SOURCES})

target_link_libraries(MyProjectTests gtest_main)

add_test(NAME MyProjectTests COMMAND MyProjectTests)
