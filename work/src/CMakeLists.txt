add_executable(a.out
  main.cpp
  hello.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c17 -Wall -Wextra -Wpedantic")

target_include_directories(a.out
  PUBLIC ${PROJECT_SOURCE_DIR}/include/
)