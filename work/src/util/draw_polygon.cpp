#include <algorithm>
#include <fstream>
#include <iostream>
#include <png.h>
#include <string>
#include <vector>

#include "const.hpp"
#include "interface.hpp"

void draw_polygon(png_bytep *row_pointers, int color, std::vector<Coord> vertices)
{
    int min_x = std::min_element(vertices.begin(), vertices.end(), [](Coord a, Coord b)
                                 { return a.x < b.x; })
                    ->x;
    int min_y = std::min_element(vertices.begin(), vertices.end(), [](Coord a, Coord b)
                                 { return a.y < b.y; })
                    ->y;
    int max_x = std::max_element(vertices.begin(), vertices.end(), [](Coord a, Coord b)
                                 { return a.x < b.x; })
                    ->x;
    int max_y = std::max_element(vertices.begin(), vertices.end(), [](Coord a, Coord b)
                                 { return a.y < b.y; })
                    ->y;

    for (int y = min_y; y <= max_y; y++)
    {
        png_bytep row = row_pointers[y];
        for (int x = min_x; x <= max_x; x++)
        {
            bool inside = false;
            for (unsigned int i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++)
            {
                if (((vertices[i].y <= y) && (y < vertices[j].y)) || ((vertices[j].y <= y) && (y < vertices[i].y)))
                {
                    if (x < (vertices[j].x - vertices[i].x) * (y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)
                    {
                        inside = !inside;
                    }
                }
            }
            if (inside)
            {
                png_bytep px = &(row[x * 4]);
                px[0] = color >> 16 & 0xff;
                px[1] = color >> 8 & 0xff;
                px[2] = color >> 0 & 0xff;
                px[3] = MAX_COLOR_VALUE;
            }
        }
    }
}
