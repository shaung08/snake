cmake_minimum_required(VERSION 2.6)
project(main)

add_executable(main main.cpp snake.cpp canvas.cpp keyboard.cpp food.cpp)


target_link_libraries(main pthread)