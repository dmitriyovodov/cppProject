cmake_minimum_required(VERSION 3.10)

project(MyProject CXX)

add_executable(MyApp main.cpp sim.cpp levels.cpp utils.cpp platform_common.cpp renderer.cpp)

# Добавляем директивы для компиляции файлов
target_sources(MyApp PRIVATE sim.cpp levels.cpp utils.cpp platform_common.cpp renderer.cpp)

# Добавляем include-директивы для библиотек
target_include_directories(MyApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем библиотеки для линковки
target_link_libraries(MyApp PRIVATE windows cmath vector)