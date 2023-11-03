#ifndef CONFIG_SIERPINSKI_TRIANGLE_HPP
#define CONFIG_SIERPINSKI_TRIANGLE_HPP

#include <iostream>
#include <string>

using namespace std;

struct SierpinskiTriangle
{
    int width;
    int height;
    int color_hex;
    int filling_color_hex;
    int background_color_hex;
    int triangle_size;
    int max_iterations;
    string output_file;
};

#endif
