#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <string>

#include "config.hpp"

namespace drawer {
  void mandelbrot(Mandelbrot* mandelbrot_config);
  void julia(Julia* julia_config);
  void tricorn(Tricorn* tricorn_config);
  void burning_ship(BurningShip* burning_ship_config);
  void barnsley_fern(BarnsleyFern* barnsley_fern_config);
}

#endif
