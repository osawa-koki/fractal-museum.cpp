#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "config_mandelbrot.hpp"
#include "config_julia.hpp"
#include "config_tricorn.hpp"
#include "config_burning_ship.hpp"

using namespace std;

struct Config {
  int width;
  int height;
  string output_directory;
  Mandelbrot* mandelbrot;
  Julia* julia;
  Tricorn* tricorn;
  BurningShip* burning_ship;
};

#endif
