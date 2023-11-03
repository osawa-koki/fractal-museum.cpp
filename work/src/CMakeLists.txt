SET(CMAKE_CXX_COMPILER /usr/bin/g++)

add_executable(a.out
  ./main.cpp
  ./drawer/drawer_mandelbrot.cpp
  ./drawer/drawer_julia.cpp
  ./drawer/drawer_tricorn.cpp
  ./drawer/drawer_burning_ship.cpp
  ./drawer/drawer_barnsley_fern.cpp
  ./drawer/drawer_pythagoras_tree.cpp
  ./drawer/drawer_recursive_tree.cpp
  ./config_parser.cpp
  ./function/hsl_to_rgb.cpp
  ./function/join_path.cpp
  ./util/draw_polygon.cpp
  ./util/draw_polyline.cpp
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
