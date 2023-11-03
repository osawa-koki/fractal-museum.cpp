SET(CMAKE_CXX_COMPILER /usr/bin/g++)

add_executable(a.out
  ./main.cpp
  ./drawer/mandelbrot.cpp
  ./drawer/julia.cpp
  ./config_parser.cpp
  ./function/hsl_to_rgb.cpp
  ./function/join_path.cpp
  ./lib/pugixml.cpp
)

set_target_properties(a.out PROPERTIES OUTPUT_NAME "./program.out")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic")
target_link_libraries(a.out
  PUBLIC png
)

target_include_directories(a.out
  PUBLIC ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/include/config/ ${PROJECT_SOURCE_DIR}/include/lib/
)
