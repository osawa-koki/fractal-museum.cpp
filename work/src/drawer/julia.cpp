#ifndef drawer_julia_hpp
#define drawer_julia_hpp

#include <iostream>
#include <string>
#include <png.h>
#include <iostream>
#include <fstream>

#include "function.hpp"
#include "interface.hpp"

using namespace std;

namespace drawer {

  void julia() {
    int MAX_COLOR_VALUE = 255;

    // 画像の幅と高さを指定する
    int width = 1024;
    int height = 1024;

    double x_min = -1.5;
    double x_max = 1.5;
    double y_min = -1.5;
    double y_max = 1.5;

    double cx = -0.4;
    double cy = 0.6;

    int max_iterations = 200;
    int color_base = 0;

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

        double x0 = x_min + (x_max - x_min) * x / width;
        double y0 = y_min + (y_max - y_min) * y / height;
        double x1 = x0;
        double y1 = y0;
        int i = 0;
        while (x1 * x1 + y1 * y1 <= 2 * 2 && i < max_iterations)
        {
          double x2 = x1 * x1 - y1 * y1 + cx;
          double y2 = 2 * x1 * y1 + cy;
          x1 = x2;
          y1 = y2;
          i++;
        }

        // 計算結果を色に変換する
        int color = i * 360 / max_iterations + color_base;
        HSL* hsl = new HSL();
        hsl->h = color;
        hsl->s = 100;
        hsl->l = 50;
        RGB* rgb = hsl_to_rgb(hsl);
        px[0] = rgb->r;
        px[1] = rgb->g;
        px[2] = rgb->b;
        px[3] = MAX_COLOR_VALUE;
      }
    }

    // 画像をファイルに出力する
    ofstream output_file("julia.png", ios::binary);
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

#endif
