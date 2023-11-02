#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <string>

#include "mandelbrot.hpp"
#include "julia.hpp"

namespace drawer {
  void mandelbrot(Mandelbrot* mandelbrot_config);
  void julia(Julia* julia_config);
}

#endif
