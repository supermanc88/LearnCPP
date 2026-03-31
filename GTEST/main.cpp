#include <iostream>
#include <gtest/gtest.h>

int add(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div1(int a, int b) { return a / b; }


TEST(MathTest, add) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(MathTest, sub) {
    EXPECT_EQ(sub(3, 2), 1);
}

TEST(MathTest, mul) {
    EXPECT_EQ(mul(3, 2), 6);
}

TEST(MathTest, div) {
    EXPECT_EQ(div1(3, 2), 0);
}

int main(int argc, char **argv) {
    std::cout << "MAIN RUNNING\n";
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}