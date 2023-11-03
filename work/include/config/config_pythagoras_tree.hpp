#ifndef CONFIG_PYTHAGORAS_TREE_HPP
#define CONFIG_PYTHAGORAS_TREE_HPP

#include <iostream>
#include <string>

using namespace std;

struct PythagorasTree {
  int width;
  int height;
  int color_hue_start;
  int color_hue_end;
  int background_color_hex;
  int size;
  int degree;
  int depth;
  double left;
  double bottom;
  string output_file;
};

#endif
