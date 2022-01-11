project(Graphics)

add_executable(Graphics sdl_graphics.cpp test.cpp)
target_link_libraries(Graphics SDL2 pthread SDL2_ttf)