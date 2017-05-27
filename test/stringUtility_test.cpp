#include <gtest/gtest.h>
#include "stringUtility.hpp"

TEST(StringUtility, swap_string){
    char a = 'a', b = 'b';
    utility::swap(a, b);

    EXPECT_EQ('a', b);
    EXPECT_EQ('b', a);
}

TEST(StringUtility, reverse_string) {
    std::string input = "123456789";
    const std::string output = "987654321";
    utility::reverse(input);

    EXPECT_EQ(output, input);
}

TEST(StringUtility, reverse_cstring) {
    char input[]  = "123456789";
    const char output[] = "987654321";

    utility::reverse(input);

    EXPECT_TRUE(strcmp(input, output) == 0);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
