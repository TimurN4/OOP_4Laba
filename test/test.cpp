#include <gtest/gtest.h>
#include "../include/array.hpp"
#include "../include/triangle.hpp"
#include "../include/square.hpp"
#include "../include/rectangle.hpp"

TEST(ArrayTest, DefaultConstructor) {
    array<double> arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_EQ(arr.get_capacity(), 4);
}

TEST(ArrayTest, ConstructorWithSize) {
    array<double> arr(10);
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_EQ(arr.get_capacity(), 10);
}

TEST(ArrayTest, AddElement) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr.get_capacity(), 4);
}

TEST(ArrayTest, RemoveLastElement) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    EXPECT_TRUE(arr.remove_last());
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(ArrayTest, RemoveAtIndex) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t1 = std::make_shared<triangle<double>>(p1, p2, p3);
    auto t2 = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t1);
    arr.add(t2);
    EXPECT_TRUE(arr.remove_index(0));
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrayTest, GetSize) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrayTest, GetCapacity) {
    array<double> arr(10);
    EXPECT_EQ(arr.get_capacity(), 10);
}

TEST(ArrayTest, CommonArea) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    //EXPECT_EQ(arr.common_area(), 0.5); // Площадь треугольника (0,0), (1,1), (1,0) равна 0.5
    ASSERT_TRUE(arr.common_area() == 0.5);
}

TEST(ArrayTest, OperatorBrackets) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    EXPECT_EQ(arr[0], t);
}

TEST(ArrayTest, Print) {
    array<double> arr;
    point<double> p1(0, 0);
    point<double> p2(1, 1);
    point<double> p3(1, 0);
    auto t = std::make_shared<triangle<double>>(p1, p2, p3);
    arr.add(t);
    testing::internal::CaptureStdout();
    arr.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("info about 0 figure"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}