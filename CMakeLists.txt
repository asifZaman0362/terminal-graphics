project(Graphics)

include_directories(./)
include_directories(header)
add_executable(Graphics header/graphics.h task_five.cpp)
target_link_libraries(Graphics sfml-system sfml-window sfml-graphics)
