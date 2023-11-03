#ifndef CONFIG_BARNSLEY_FERN_HPP
#define CONFIG_BARNSLEY_FERN_HPP

#include <iostream>
#include <string>

using namespace std;

struct BarnsleyFern
{
    int width;
    int height;
    double size;
    double start_x;
    double start_y;
    double zoom;
    int max_iterations;
    int color_hex;
    int background_color_hex;
    string output_file;
};

#endif
