#include <gtest/gtest.h>
#include "../sky_utils.hpp"


TEST(StringToInt64t, ReturnsValidInt64t) {
    EXPECT_EQ(sky_utils::to_int64("5678"), 5678);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}