#include "drawer.hpp"
#include "config.hpp"
#include "function.hpp"

int main()
{
    Config *config = config_parser();
    drawer::mandelbrot(config->mandelbrot);
    drawer::julia(config->julia);
    drawer::tricorn(config->tricorn);
    drawer::burning_ship(config->burning_ship);
    drawer::barnsley_fern(config->barnsley_fern);
    drawer::pythagoras_tree(config->pythagoras_tree);
}
