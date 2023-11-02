#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "mandelbrot.hpp"
#include "julia.hpp"

using namespace std;

struct Config {
  int width;
  int height;
  string output_directory;
  Mandelbrot* mandelbrot;
  Julia* julia;
};

#endif
