#ifndef UTIL_HPP
#define UTIL_HPP

void draw_polygon(png_bytep *row_pointers, int color, std::vector<Coord> vertices);
void draw_polyline(png_bytep *row_pointers, int color, std::vector<Coord> vertices);

#endif
