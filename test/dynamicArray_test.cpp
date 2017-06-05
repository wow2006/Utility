#include "dynamicArray.hpp"
#include <gtest/gtest.h>

TEST(DynamucArray, default_constructor)
{
    dynamicArray<int> x;
    x.resize(5);

    EXPECT_EQ(5, x.size());
}

TEST(DynamucArray, copy_constructor)
{
    dynamicArray<int> x = {1, 2, 3, 4, 5};
    dynamicArray<int> y(x);

    EXPECT_EQ(y.size(), y.size());
    EXPECT_EQ(x[0], y[0]);
    EXPECT_EQ(x[1], y[1]);
    EXPECT_EQ(x[2], y[2]);
    EXPECT_EQ(x[3], y[3]);
    EXPECT_EQ(x[4], y[4]);
}

TEST(DynamucArray, move_constructor)
{
    dynamicArray<int> x = {1, 2, 3, 4, 5};
    dynamicArray<int> y(std::move(x));

    EXPECT_EQ(y.size(), y.size());
    EXPECT_EQ(1, y[0]);
    EXPECT_EQ(2, y[1]);
    EXPECT_EQ(3, y[2]);
    EXPECT_EQ(4, y[3]);
    EXPECT_EQ(5, y[4]);
}

TEST(DynamucArray, initializer_list)
{
    dynamicArray<int> x = {1, 2, 3, 4, 5};

    EXPECT_EQ(5, x.size());
    EXPECT_EQ(1, x[0]);
    EXPECT_EQ(2, x[1]);
    EXPECT_EQ(3, x[2]);
    EXPECT_EQ(4, x[3]);
    EXPECT_EQ(5, x[4]);
}

TEST(DynamucArray, begin)
{
    dynamicArray<int> x = {1, 2, 3, 4, 5};
    EXPECT_EQ(1, *x.begin());
}

TEST(DynamucArray, begin_const)
{
    const dynamicArray<int> x = {1, 2, 3, 4, 5};
    EXPECT_EQ(1, *x.begin());
}

TEST(DynamucArray, end)
{
    dynamicArray<int> x = {1, 2, 3, 4, 5};
    EXPECT_EQ(5, *(x.end()-1));
}

TEST(DynamucArray, end_const)
{
    const dynamicArray<int> x = {1, 2, 3, 4, 5};
    EXPECT_EQ(5, *(x.end()-1));
}


