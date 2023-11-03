#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "mandelbrot_config.hpp"
#include "julia_config.hpp"
#include "tricorn_config.hpp"

using namespace std;

struct Config {
  int width;
  int height;
  string output_directory;
  Mandelbrot* mandelbrot;
  Julia* julia;
  Tricorn* tricorn;
};

#endif
