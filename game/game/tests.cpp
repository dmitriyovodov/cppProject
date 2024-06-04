#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <vector>
#include "levels.cpp"

TEST_CASE("level1_test") {
    std::vector<std::vector<int>> test = { {35, 600}, {190, 600}, {345, 600}, {500, 600},
        {655, 600}, {810, 600}, {965, 600}, {1120, 600},
        {35, 500}, {190, 500}, {345, 500}, {500, 500},
        {655, 500}, {810, 500}, {965, 500}, {1120, 500} };
    std::vector<std::vector<int>> blocks = initialize_level1();
    bool result = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (blocks[i][j] != test[i][j]) {
                result = false;
            }
        }
    }
    CHECK(result == true);
}
