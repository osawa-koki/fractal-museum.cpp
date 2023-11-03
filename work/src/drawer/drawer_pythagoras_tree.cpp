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
#include "config_pythagoras_tree.hpp"

using namespace std;

namespace drawer {

  vector<Coord> pythagoras_tree_get_left_points(double x, double y, int size, int angle, int degree) {
    vector<Coord> points(4);
    points[0] = {x, y};
    points[1] = {
      x + cos((angle + degree) * M_PI / 180.0) * size,
      y - sin((angle + degree) * M_PI / 180.0) * size,
    };
    points[2] = {
      x + cos((angle + degree + 45) * M_PI / 180.0) * size * sqrt(2),
      y - sin((angle + degree + 45) * M_PI / 180.0) * size * sqrt(2),
    };
    points[3] = {
      x + cos((angle + degree + 90) * M_PI / 180.0) * size,
      y - sin((angle + degree + 90) * M_PI / 180.0) * size,
    };
    return points;
  }
  vector<Coord> pythagoras_tree_get_right_points(double x, double y, int size, int angle, int degree) {
    vector<Coord> points(4);
    points[0] = {x, y};
    points[1] = {
      x + cos((angle + degree) * M_PI / 180.0) * size,
      y - sin((angle + degree) * M_PI / 180.0) * size,
    };
    points[2] = {
      x + cos((angle + degree + 45) * M_PI / 180.0) * size * sqrt(2),
      y - sin((angle + degree + 45) * M_PI / 180.0) * size * sqrt(2),
    };
    points[3] = {
      x + cos((angle + degree + 90) * M_PI / 180.0) * size,
      y - sin((angle + degree + 90) * M_PI / 180.0) * size,
    };
    return points;
  }

  void pythagoras_tree_rec_draw(png_bytep *row_pointers, Coord p1, Coord p2, int size, int angle, int degree, int n, int i, int current_color, int color_step) {
    if (n == 0) return;

    HSL* hsl = new HSL();
    hsl->h = current_color % 360;
    hsl->s = 100;
    hsl->l = 50;
    RGB* rgb = hsl_to_rgb(hsl);

    int color = (rgb->r << 16) + (rgb->g << 8) + (rgb->b << 0);

    // 左側
    {
      double smalled_size = cos(degree * M_PI / 180) * size;
      vector<Coord> points = pythagoras_tree_get_left_points(p1.x, p1.y, smalled_size, angle, degree);
      draw_polygon(
        row_pointers,
        color,
        points);
      pythagoras_tree_rec_draw(
        row_pointers,
        points[3],
        points[2],
        smalled_size,
        angle + degree,
        degree,
        n - 1,
        i + 1,
        current_color + color_step,
        color_step
      );
    }

    // 右側
    {
      double smalled_size = sin(degree * M_PI / 180) * size;
      vector<Coord> points = pythagoras_tree_get_right_points(p2.x, p2.y, smalled_size, angle, degree);
      draw_polygon(
        row_pointers,
        color,
        points);
      pythagoras_tree_rec_draw(
        row_pointers,
        points[2],
        points[1],
        smalled_size,
        angle - (90 - degree),
        degree,
        n - 1,
        i + 1,
        current_color + color_step,
        color_step
      );
    }
  }

  void pythagoras_tree(PythagorasTree* pythagoras_tree_config) {
    int width = pythagoras_tree_config->width;
    int height = pythagoras_tree_config->height;

    int color_hue_start = pythagoras_tree_config->color_hue_start;
    int color_hue_end = pythagoras_tree_config->color_hue_end;
    int color_step = (color_hue_end - color_hue_start) / pythagoras_tree_config->depth;
    int background_color = pythagoras_tree_config->background_color_hex;

    int degree = pythagoras_tree_config->degree;
    int size = pythagoras_tree_config->size;
    int depth = pythagoras_tree_config->depth;

    double left = pythagoras_tree_config->left;
    double bottom = pythagoras_tree_config->bottom;

    double box_size = (width + height) / 2 * size / 100;
    double left_size = width * left / 100;
    double bottom_size = height * bottom / 100;

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

    HSL* hsl = new HSL();
    hsl->h = color_hue_start % 360;
    hsl->s = 100;
    hsl->l = 50;
    RGB* rgb = hsl_to_rgb(hsl);

    int color = (rgb->r << 16) + (rgb->g << 8) + (rgb->b << 0);

    draw_polygon(
      row_pointers,
      color,
      vector<Coord>{
        Coord{ left_size - box_size / 2, height - bottom_size - box_size },
        Coord{ left_size + box_size / 2, height - bottom_size - box_size },
        Coord{ left_size + box_size / 2, height - bottom_size },
        Coord{ left_size - box_size / 2, height - bottom_size }
      }
    );

    pythagoras_tree_rec_draw(
      row_pointers,
      Coord{ left_size - box_size / 2, height - bottom_size - box_size },
      Coord{ left_size - box_size / 2 + box_size, height - bottom_size - box_size },
      box_size,
      0,
      degree,
      depth,
      1,
      color_hue_start,
      color_step
    );

    // 画像をファイルに出力する
    ofstream output_file(pythagoras_tree_config->output_file, ios::binary);
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
