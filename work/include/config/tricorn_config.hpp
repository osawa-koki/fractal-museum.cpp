#ifndef CONFIG_TRICORN_HPP
#define CONFIG_TRICORN_HPP

#include <iostream>
#include <string>

using namespace std;

struct Tricorn {
  int width;
  int height;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int threshold;
  int max_iterations;
  int color_hue_base;
  string output_file;
};

#endif
