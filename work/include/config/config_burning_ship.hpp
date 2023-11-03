#ifndef CONFIG_BURNING_SHIP_HPP
#define CONFIG_BURNING_SHIP_HPP

#include <iostream>
#include <string>

using namespace std;

struct BurningShip
{
    int width;
    int height;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    int threshold;
    int max_iterations;
    int color_hue_base;
    string output_file;
};

#endif
