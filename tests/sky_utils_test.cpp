#include <gtest/gtest.h>
#include "../sky_utils.hpp"

// Both names must be valid C++ identifiers, and they should not contain any underscores (_)
TEST(StringToInt64t, ReturnsValidInt64t) {
    EXPECT_EQ(sky_utils::to_int64("5678"), 5678);
}

TEST(StringToInt64t, HandlesEmptyString) {
    EXPECT_EQ(sky_utils::to_int64(""), std::nullopt);
}

TEST(StringToInt64t, HandlesInvalidString) {
    EXPECT_EQ(sky_utils::to_int64("bob"), std::nullopt);
}

TEST(StringToInt64t, HandlesMaxValue) {
    EXPECT_EQ(sky_utils::to_int64("9223372036854775807"), std::numeric_limits<int64_t>::max());
}

TEST(StringToInt64t, HandlesMinValue) {
    EXPECT_EQ(sky_utils::to_int64("-9223372036854775808"), std::numeric_limits<int64_t>::min());
}



static std::vector<std::string> expected_sstv{ "1", "2", "3", "4", "5", "6", "7", "8" };
TEST(SplitStringToVector, SplitsStringOnDefaultDelimiter) {
    EXPECT_EQ(sky_utils::split_str_to_vector("1 2 3 4 5 6 7 8"), expected_sstv);
}

TEST(SplitStringToVector, SplitsStringOnCommaDelimiter) {
    EXPECT_EQ(sky_utils::split_str_to_vector("1,2,3,4,5,6,7,8", ','), expected_sstv);
}

// vally-of-ghosts.txt has 27 . so 28 lines
TEST(SplitStringToVector, EmptyString) {
    EXPECT_EQ(sky_utils::split_str_to_vector("", ','), std::vector<std::string>(1));
}

TEST(SplitStringToVector, LongTextToLinesOnFullStop) {
    auto test = sky_utils::file_to_string("./data/valley-of-ghosts.txt");
    auto vec = sky_utils::split_str_to_vector(test, '.');
    sky_utils::print_vector_of_strings(vec);
    EXPECT_EQ(vec.size(), 28);
}

