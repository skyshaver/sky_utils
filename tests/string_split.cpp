#include <gtest/gtest.h>
#include "../sky_utils.hpp"

static std::vector<std::string> expected{ "1", "2", "3", "4", "5", "6", "7", "8" };
TEST(SplitStringToVector, SplitsStringOnDefaultDelimiter) {
    EXPECT_EQ(sky_utils::split_str_to_vector("5 6 7 8"), 5678);
}