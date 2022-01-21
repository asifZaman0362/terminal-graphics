project(Graphics)

add_executable(Graphics graphics.h test.cpp)
target_link_libraries(Graphics sfml-system sfml-window sfml-graphics)