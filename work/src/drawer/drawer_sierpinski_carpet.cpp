#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <png.h>
#include <string>
#include <vector>

#include "const.hpp"
#include "function.hpp"
#include "interface.hpp"
#include "util.hpp"

using namespace std;

namespace private_sierpinski_carpet
{
    struct GlobalStruct
    {
        int color_hex;
        int filling_color_hex;
        int max_iterations;
    };

    vector<Coord> cross_join(vector<double> arg)
    {
        vector<Coord> vertices = {};
        for (int i = 0; i < arg.size(); i++)
        {
            for (int j = 0; j < arg.size(); j++)
            {
                vertices.push_back(Coord{arg[i], arg[j]});
            }
        }
        return vertices;
    }

    void rec_fx(png_bytep *row_pointers, GlobalStruct global_struct, int x, int y, int size, int n)
    {
        if (global_struct.max_iterations < n)
            return;

        vector<double> xys = {1 / 9.0 * size, 4 / 9.0 * size, 7 / 9.0 * size};
        vector<Coord> vertices = cross_join(xys);

        for (int i = 0; i < vertices.size(); i++)
        {
            Coord xy = vertices[i];
            vector<Coord> points = {
                Coord{x + xy.x, y + xy.y},
                Coord{x + xy.x + size / 9.0, y + xy.y},
                Coord{x + xy.x + size / 9.0, y + xy.y + size / 9.0},
                Coord{x + xy.x, y + xy.y + size / 9.0}};
            draw_polygon(row_pointers, global_struct.color_hex, points);
            rec_fx(row_pointers, global_struct, x + xy.x - size / 9.0, y + xy.y - size / 9.0, size / 3.0, n + 1);
        }
    }
}

using namespace private_sierpinski_carpet;

namespace drawer
{

    void sierpinski_carpet(SierpinskiCarpet *sierpinski_carpet_config)
    {
        int width = sierpinski_carpet_config->width;
        int height = sierpinski_carpet_config->height;

        int color = sierpinski_carpet_config->color_hex;
        int filling_color = sierpinski_carpet_config->filling_color_hex;
        int background_color = sierpinski_carpet_config->background_color_hex;

        int carpet_size = sierpinski_carpet_config->carpet_size;
        int max_iterations = sierpinski_carpet_config->max_iterations;

        GlobalStruct global_struct = {
            color,
            filling_color,
            max_iterations};

        // 画像のデータを格納する配列を確保する
        png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
        for (int y = 0; y < height; y++)
        {
            row_pointers[y] = (png_byte *)malloc(sizeof(png_byte) * width * 4);
        }

        for (int y = 0; y < height; y++)
        {
            png_bytep row = row_pointers[y];
            for (int x = 0; x < width; x++)
            {
                png_bytep px = &(row[x * 4]);
                px[0] = (background_color >> 16) & 0xff;
                px[1] = (background_color >> 8) & 0xff;
                px[2] = (background_color >> 0) & 0xff;
                px[3] = MAX_COLOR_VALUE;
            }
        }

        int size = width * carpet_size / 100;
        int start = (height - size) / 2;
        int size_inside = size / 3;
        int start_inside = start + size_inside;

        {
            std::vector<Coord> vertices = {
                Coord{start, start},
                Coord{start, start + size},
                Coord{start + size, start + size},
                Coord{start + size, start}};
            draw_polygon(row_pointers, filling_color, vertices);
        }
        {
            std::vector<Coord> vertices = {
                Coord{start_inside, start_inside},
                Coord{start_inside, start_inside + size_inside},
                Coord{start_inside + size_inside, start_inside + size_inside},
                Coord{start_inside + size_inside, start_inside}};
            draw_polygon(row_pointers, color, vertices);
        }

        rec_fx(row_pointers, global_struct, start, start, size, 1);

        // 画像をファイルに出力する
        ofstream output_file(sierpinski_carpet_config->output_file, ios::binary);
        png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info = png_create_info_struct(png);
        png_set_write_fn(
            png, &output_file, [](png_structp png, png_bytep data, png_size_t length)
            { ((ostream *)png_get_io_ptr(png))->write((char *)data, length); },
            nullptr);
        png_set_IHDR(
            png,
            info,
            width, height,
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

        png_write_info(png, info);
        png_write_image(png, row_pointers);
        png_write_end(png, NULL);

        // メモリを解放する
        for (int y = 0; y < height; y++)
        {
            free(row_pointers[y]);
        }
        free(row_pointers);

        return;
    }
}
