project(Graphics)

include_directories(./)
add_executable(Graphics graphics.h dda.cpp)
target_link_libraries(Graphics sfml-system sfml-window sfml-graphics)