#ifndef CONFIG_RECURSIVE_TREE_HPP
#define CONFIG_RECURSIVE_TREE_HPP

#include <iostream>
#include <string>

using namespace std;

struct RecursiveTree {
  int width;
  int height;
  int shrink;
  int length;
  int angle;
  int max_iterations;
  int stroke_width;
  int color_hex;
  int background_color_hex;
  string output_file;
};

#endif
