#include <iostream>
#include <fstream>
#include <png.h>
#include <string>

#include "const.hpp"
#include "function.hpp"
#include "interface.hpp"
#include "config_burning_ship.hpp"

using namespace std;

namespace drawer
{

    void burning_ship(BurningShip *burning_ship_config)
    {
        int width = burning_ship_config->width;
        int height = burning_ship_config->height;

        double x_min = burning_ship_config->x_min;
        double x_max = burning_ship_config->x_max;
        double y_min = burning_ship_config->y_min;
        double y_max = burning_ship_config->y_max;

        double x_range = x_max - x_min;
        double y_range = y_max - y_min;
        double x_step = x_range / width;
        double y_step = y_range / height;

        int threshold = burning_ship_config->threshold;
        int max_iterations = burning_ship_config->max_iterations;
        int color_hue_base = burning_ship_config->color_hue_base;

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

                double x0 = x_min + x * x_step;
                double y0 = y_min + y * y_step;
                double x1 = 0;
                double y1 = 0;
                int i = 0;
                while (x1 * x1 + y1 * y1 < threshold && i < max_iterations)
                {
                    double x2 = abs(x1 * x1 - y1 * y1 + x0);
                    double y2 = abs(2 * x1 * y1 + y0);
                    x1 = x2;
                    y1 = y2;
                    i++;
                }
                if (i == max_iterations)
                {
                    px[0] = 0;
                    px[1] = 0;
                    px[2] = 0;
                    px[3] = MAX_COLOR_VALUE;
                }
                else
                {
                    int hue = (i * 360 / max_iterations + color_hue_base) % 360;
                    HSL *hsl = new HSL();
                    hsl->h = hue;
                    hsl->s = 100;
                    hsl->l = 50;
                    RGB *rgb = hsl_to_rgb(hsl);
                    px[0] = rgb->r;
                    px[1] = rgb->g;
                    px[2] = rgb->b;
                    px[3] = MAX_COLOR_VALUE;
                }
            }
        }

        // 画像をファイルに出力する
        ofstream output_file(burning_ship_config->output_file, ios::binary);
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
