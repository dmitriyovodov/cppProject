
/**
* Функция initialize_level3 устанавливает координаты блоков для третьего уровня.
* @return Ничего не возвращает.
*/
std::vector<std::vector<int>> initialize_level3() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}

/**
* Функция initialize_level2 устанавливает координаты блоков для второго уровня.
* @return Ничего не возвращает.
*/
std::vector<std::vector<int>> initialize_level2() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}

/**
* Функция initialize_level1 устанавливает координаты блоков для первого уровня.
* @return Ничего не возвращает.
*/
std::vector<std::vector<int>> initialize_level1() {
	std::vector<std::vector<int>> blocks;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			blocks.push_back({ j * 155 + 35, 600 - i * 100 });
		}
	}
	return blocks;
}