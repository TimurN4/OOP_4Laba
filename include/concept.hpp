#pragma once
#include <type_traits>
#include <concepts>

template <typename T>
concept scalar_type = std::is_integral_v<T> || std::is_floating_point_v<T>;
