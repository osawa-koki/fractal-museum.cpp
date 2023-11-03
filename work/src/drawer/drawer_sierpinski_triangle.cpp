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

namespace private_sierpinski_triangle
{
    struct GlobalStruct
    {
        int color_hex;
        int filling_color_hex;
        int max_iterations;
    };

    void draw(png_bytep *row_pointers, GlobalStruct global_struct, int x, int y, int size)
    {
        int p1_x = x + size / 2;
        int p1_y = y - sin(-60 * M_PI / 180) * size;
        int p2_x = x + size;
        int p2_y = y;
        std::vector<Coord> vertices = {
            Coord{x, y},
            Coord{p1_x, p1_y},
            Coord{p2_x, p2_y}};
        draw_polygon(row_pointers, global_struct.filling_color_hex, vertices);
    }

    void rec_fx(png_bytep *row_pointers, GlobalStruct global_struct, int x, int y, int size, int n)
    {
        if (global_struct.max_iterations < n)
            return;

        int p1_x = cos(240 * M_PI / 180) * 1 / 4 * size + x;
        int p1_y = y - sin(240 * M_PI / 180) * 1 / 4 * size;
        int p2_x = cos(240 * M_PI / 180) * 3 / 4 * size + x;
        int p2_y = y - sin(240 * M_PI / 180) * 3 / 4 * size;
        int p3_x = p2_x + size / 2;
        int p3_y = p2_y;

        draw(row_pointers, global_struct, p1_x, p1_y, size / 4);
        draw(row_pointers, global_struct, p2_x, p2_y, size / 4);
        draw(row_pointers, global_struct, p3_x, p3_y, size / 4);

        rec_fx(row_pointers, global_struct, x, y, size / 2, n + 1);
        rec_fx(row_pointers, global_struct, cos(240 * M_PI / 180) * 1 / 2 * size + x, y - sin(240 * M_PI / 180) * 1 / 2 * size, size / 2, n + 1);
        rec_fx(row_pointers, global_struct, cos(-60 * M_PI / 180) * 1 / 2 * size + x, y - sin(-60 * M_PI / 180) * 1 / 2 * size, size / 2, n + 1);
    }
}

using namespace private_sierpinski_triangle;

namespace drawer
{

    void sierpinski_triangle(SierpinskiTriangle *sierpinski_triangle_config)
    {
        int width = sierpinski_triangle_config->width;
        int height = sierpinski_triangle_config->height;

        int color = sierpinski_triangle_config->color_hex;
        int filling_color = sierpinski_triangle_config->filling_color_hex;
        int background_color = sierpinski_triangle_config->background_color_hex;

        int triangle_size = sierpinski_triangle_config->triangle_size;
        int max_iterations = sierpinski_triangle_config->max_iterations;

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

        int size = width * triangle_size / 100;
        int start = (height - (sqrt(3) * height * triangle_size / 100 / 2)) / 2;

        int p1_x = cos(240 * M_PI / 180) * size / 2 + width / 2;
        int p1_y = start - sin(240 * M_PI / 180) * size / 2;
        int p2_x = cos(-60 * M_PI / 180) * size / 2 + p1_x;
        int p2_y = p1_y - sin(-60 * M_PI / 180) * size / 2;

        int _p2_x = cos(240 * M_PI / 180) * size + width / 2;
        int _p2_y = start - sin(240 * M_PI / 180) * size;

        {
            std::vector<Coord> vertices = {
                Coord{width / 2, start},
                Coord{_p2_x, _p2_y},
                Coord{_p2_x + size, _p2_y}};
            draw_polygon(row_pointers, color, vertices);
        }
        {
            std::vector<Coord> vertices = {
                Coord{p1_x, p1_y},
                Coord{p2_x, p2_y},
                Coord{p1_x + size / 2, p1_y}};
            draw_polygon(row_pointers, filling_color, vertices);
        }

        rec_fx(row_pointers, global_struct, width / 2, start, size, 1);

        // 画像をファイルに出力する
        ofstream output_file(sierpinski_triangle_config->output_file, ios::binary);
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
