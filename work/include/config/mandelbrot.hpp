#ifndef CONFIG_MANDELBROT_HPP
#define CONFIG_MANDELBROT_HPP

using namespace std;

struct Mandelbrot {
  int width;
  int height;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int max_iterations;
  string output_file;
};

#endif
