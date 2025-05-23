cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME example)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS FALSE)
include_directories("src")
set(SRC_FILES
              src/Object.cpp
              src/Ship.cpp
              src/Bullet.cpp
              src/Timer.cpp
              src/Game.cpp
              src/main.cpp
              src/Block.cpp
              src/Enemy.cpp
              src/Particle.cpp
)

add_executable("${PROJECT_NAME}" ${SRC_FILES})
add_subdirectory("ext/SFML")
include_directories("ext/SFML/include/")
link_directories("ext/SFML/lib/")
target_include_directories("${PROJECT_NAME}" PRIVATE ext/SFML/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio sfml-graphics sfml-main sfml-network sfml-system sfml-window)
file(COPY "images/" DESTINATION "${PROJECT_BINARY_DIR}/Debug")
file(COPY "images/" DESTINATION "${PROJECT_BINARY_DIR}/Release")