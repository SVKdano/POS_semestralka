cmake_minimum_required(VERSION 3.18)
project(Bulanci)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bulanci cpp/main.cpp head/game.h cpp/game.cpp head/block.h cpp/block.cpp head/player.h cpp/player.cpp head/bullet.h cpp/bullet.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)

target_link_libraries(Bulanci sfml-system sfml-window sfml-graphics sfml-audio sfml-network)