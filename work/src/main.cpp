#include "hello.hpp"
#include "make_image.hpp"
#include "drawer.hpp"

int main()
{
    hello();
    make_image();
    drawer::mandelbrot();
    drawer::julia();
}
