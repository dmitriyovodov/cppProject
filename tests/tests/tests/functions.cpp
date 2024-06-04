#include <vector>


std::vector<std::vector<int>> initialize_level3() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}

std::vector<std::vector<int>> initialize_level2() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}

std::vector<std::vector<int>> initialize_level1() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}

inline int clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}