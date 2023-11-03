#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <string>

#include "config.hpp"

namespace drawer {
  void mandelbrot(Mandelbrot* mandelbrot_config);
  void julia(Julia* julia_config);
  void tricorn(Tricorn* tricorn_config);
}

#endif
