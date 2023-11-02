add_executable(a.out
  main.cpp
  hello.cpp
)

target_include_directories(a.out
  PUBLIC ${PROJECT_SOURCE_DIR}/include/
)
