cmake_minimum_required(VERSION 3.10)

project(MyProject CXX)

enable_testing()
add_test(NAME my_test COMMAND my_test)

add_executable(my_test tests.cpp)
target_link_libraries(my_test doctest)

add_executable(MyApp main.cpp sim.cpp levels.cpp utils.cpp platform_common.cpp renderer.cpp)

# Добавляем директивы для компиляции файлов
target_sources(MyApp PRIVATE sim.cpp levels.cpp utils.cpp platform_common.cpp renderer.cpp)

# Добавляем include-директивы для библиотек
target_include_directories(MyApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем библиотеки для линковки
target_link_libraries(MyApp PRIVATE windows cmath vector)


