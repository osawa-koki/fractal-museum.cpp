#include <iostream>
#include <fstream>
#include <png.h>
#include <string>

#include "const.hpp"
#include "function.hpp"
#include "interface.hpp"
#include "config_barnsley_fern.hpp"

using namespace std;

namespace drawer {

  void barnsley_fern(BarnsleyFern* burnsley_fern_config) {
    int width = burnsley_fern_config->width;
    int height = burnsley_fern_config->height;

    double size = burnsley_fern_config->size;
    double start_x = burnsley_fern_config->start_x;
    double start_y = burnsley_fern_config->start_y;
    double zoom = burnsley_fern_config->zoom;
    int max_iterations = burnsley_fern_config->max_iterations;
    int color_hex = burnsley_fern_config->color_hex;
    int background_color_hex = burnsley_fern_config->background_color_hex;

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
        px[0] = (background_color_hex >> 16) & 0xff;
        px[1] = (background_color_hex >> 8) & 0xff;
        px[2] = (background_color_hex >> 0) & 0xff;
        px[3] = MAX_COLOR_VALUE;
      }
    }

    double x = 0, y = 0;

    for (int i = 0; i < max_iterations; i++) {
      int p_x = (zoom * x + start_x * width / 100);
      int p_y = (height - ((size * height / 1000) * y + (start_y * height / 100)));
      if (p_x >= 0 && p_x < width && p_y >= 0 && p_y < height) {
        png_bytep row = row_pointers[p_y];
        png_bytep px = &(row[p_x * 4]);
        px[0] = (color_hex >> 16) & 0xff;
        px[1] = (color_hex >> 8) & 0xff;
        px[2] = (color_hex >> 0) & 0xff;
        px[3] = MAX_COLOR_VALUE;
      }

      double r = rand() % 100;
      double xn = x, yn = y;
      if (r < 1) {
        x = 0;
        y = 0.16 * yn;
      } else if (r < 86) {
        x = 0.85 * xn + 0.04 * yn;
        y = -0.04 * xn + 0.85 * yn + 1.6;
      } else if (r < 93) {
        x = 0.20 * xn - 0.26 * yn;
        y = 0.23 * xn + 0.22 * yn + 1.6;
      } else {
        x = -0.15 * xn + 0.28 * yn;
        y = 0.26 * xn + 0.24 * yn + 0.44;
      }
    }

    // 画像をファイルに出力する
    ofstream output_file(burnsley_fern_config->output_file, ios::binary);
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
