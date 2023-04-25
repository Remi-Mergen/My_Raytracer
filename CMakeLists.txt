project(raytracer)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

message("> Compiling mgl...")

set(SOURCE src/main.cpp src/Object.cpp src/Sphere.cpp src/Vec3.cpp src/Rect3.cpp src/Ray.cpp src/Camera.cpp)

add_compile_options(-Wall -Wextra -std=c++2a)

add_executable(raytracer ${SOURCE})

set_target_properties(raytracer PROPERTIES
        LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        )

target_include_directories(raytracer PUBLIC ./include/)

# Set the include and library paths for SFML
include_directories(/opt/homebrew/Cellar/sfml/2.5.1_2/include)
link_directories(/opt/homebrew/Cellar/sfml/2.5.1_2/lib)

# Manually find the SFML libraries
find_library(SFML_AUDIO_LIBRARY sfml-audio /opt/homebrew/Cellar/sfml/2.5.1_2/lib)
find_library(SFML_WINDOW_LIBRARY sfml-window /opt/homebrew/Cellar/sfml/2.5.1_2/lib)
find_library(SFML_SYSTEM_LIBRARY sfml-system /opt/homebrew/Cellar/sfml/2.5.1_2/lib)
find_library(SFML_GRAPHICS_LIBRARY sfml-graphics /opt/homebrew/Cellar/sfml/2.5.1_2/lib)

# Link the SFML libraries to your target
target_link_libraries(raytracer ${SFML_AUDIO_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_SYSTEM_LIBRARY} ${SFML_GRAPHICS_LIBRARY})

message("  MGL compiled !")
