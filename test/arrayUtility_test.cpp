#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>
#include "array.hpp"

TEST(arrayUtility, array_allocation) {
    utility::array<int, 5> test = {1, 2, 3, 4, 5};
    const int arraySize = test.size;
    EXPECT_EQ(5, arraySize);
    EXPECT_EQ(1, test[0]);
    EXPECT_EQ(2, test[1]);
    EXPECT_EQ(3, test[2]);
    EXPECT_EQ(4, test[3]);
    EXPECT_EQ(5, test[4]);
}

TEST(arrayUtility, array_forRange) {
    utility::array<int, 5> test;
    int i = 0;
    for (auto& item : test) item = i++;
    i = 0;
    for (auto& item : test) EXPECT_EQ(i++, item);
}

TEST(arrayUtility, array_cout) {
    std::stringstream output;
    const std::string testString = "1 2 3 4 5 \n";

    utility::array<int, 5> test = {1, 2, 3, 4, 5};
    output << test;
    EXPECT_EQ(output.str(), testString);
}

TEST(arrayUtility, array_sum) {
    utility::array<int, 5> test = {1, 2, 3, 4, 5};

    EXPECT_EQ(15.0, utility::sum(test));
}
