#ifndef CONFIG_JULIA_HPP
#define CONFIG_JULIA_HPP

using namespace std;

struct Julia {
  int width;
  int height;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int max_iterations;
  double cx;
  double cy;
  int color_hue_base;
  string output_file;
};

#endif
