#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector"
#include "levels.cpp"


TEST_CASE("level1_test") {
    std::vector<std::vector<int>> test = { 
        {35, 600}, {190, 600}, {345, 600}, {500, 600},
        {655, 600}, {810, 600}, {965, 600}, {1120, 600},
        {35, 500}, {190, 500}, {345, 500}, {500, 500},
        {655, 500}, {810, 500}, {965, 500}, {1120, 500} 
    };
    std::vector<std::vector<int>> result = initialize_level1();
    CHECK(result == test);
}

TEST_CASE("level2_test") {
    std::vector<std::vector<int>> test = { 
        {35, 600}, {190, 600}, {345, 600}, {500, 600},
        {655, 600}, {810, 600}, {965, 600}, {1120, 600},
        {35, 500}, {190, 500}, {345, 500}, {500, 500},
        {655, 500}, {810, 500}, {965, 500}, {1120, 500},
        {35, 400}, {190, 400}, {345, 400}, {500, 400},
        {655, 400}, {810, 400}, {965, 400}, {1120, 400} 
    };
    std::vector<std::vector<int>> result = initialize_level2();
    CHECK(result == test);
}

TEST_CASE("level3_test") {
    std::vector<std::vector<int>> test = {
        {35, 600}, {190, 600}, {345, 600}, {500, 600},
        {655, 600}, {810, 600}, {965, 600}, {1120, 600},
        {35, 500}, {190, 500}, {345, 500}, {500, 500},
        {655, 500}, {810, 500}, {965, 500}, {1120, 500},
        {35, 400}, {190, 400}, {345, 400}, {500, 400},
        {655, 400}, {810, 400}, {965, 400}, {1120, 400},
        {35, 300}, {190, 300}, {345, 300}, {500, 300},
        {655, 300}, {810, 300}, {965, 300}, {1120, 300}
    };
    std::vector<std::vector<int>> result = initialize_level3();
    CHECK(result == test);
}

TEST_CASE("clamp_test_1") {
    int result = clamp(10, 20, 30);
    CHECK(result == 20);
}

TEST_CASE("clamp_test_2") {
    int result = clamp(10, 40, 30);
    CHECK(result == 30);
}

TEST_CASE("clamp_test_3") {
    int result = clamp(10, 5, 30);
    CHECK(result == 10);
}

TEST_CASE("clamp_test_4") {
    int result = clamp(1, -4, 4);
    CHECK(result == 1);
}

TEST_CASE("clamp_test_5") {
    int result = clamp(1000, 4000, 3000);
    CHECK(result == 3000);
}