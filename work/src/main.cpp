#include "drawer.hpp"
#include "config.hpp"
#include "function.hpp"

int main()
{
    Config *config = config_parser();
    drawer::mandelbrot(config->mandelbrot);
    drawer::julia(config->julia);
}
