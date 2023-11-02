#include <iostream>
#include <string>

#include "pugixml.hpp"
#include "config.hpp"
#include "function.hpp"

using namespace std;

Config* config_parser() {
  // XMLファイルを開く
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file("config.xml");

  if (!result) {
    cerr << "XMLファイルの読み込みに失敗しました。" << endl;
    cerr << result.description() << endl;
    return nullptr;
  }

  // ルート要素を取得する
  pugi::xml_node config_node = doc.child("config");
  if (config_node.empty()) {
    cerr << "ルート要素が見つかりませんでした。" << endl;
    return nullptr;
  }

  Config* config = new Config();

  pugi::xml_node width_node = config_node.child("width");
  pugi::xml_node height_node = config_node.child("height");
  pugi::xml_node output_directory_node = config_node.child("output_directory");

  int width = stoi(width_node.child_value());
  int height = stoi(height_node.child_value());

  config->width = width;
  config->height = height;
  config->output_directory = output_directory_node.child_value();

  pugi::xml_node mandelbrot_node = config_node.child("mandelbrot");
  Mandelbrot* mandelbrot = new Mandelbrot();
  mandelbrot->width = width;
  mandelbrot->height = height;
  mandelbrot->x_min = stod(mandelbrot_node.child("x_min").child_value());
  mandelbrot->x_max = stod(mandelbrot_node.child("x_max").child_value());
  mandelbrot->y_min = stod(mandelbrot_node.child("y_min").child_value());
  mandelbrot->y_max = stod(mandelbrot_node.child("y_max").child_value());
  mandelbrot->max_iterations = stoi(mandelbrot_node.child("max_iterations").child_value());
  mandelbrot->output_file = join_path(config->output_directory, mandelbrot_node.child("output_file").child_value());
  config->mandelbrot = mandelbrot;

  pugi::xml_node julia_node = config_node.child("julia");
  Julia* julia = new Julia();
  julia->width = width;
  julia->height = height;
  julia->x_min = stod(julia_node.child("x_min").child_value());
  julia->x_max = stod(julia_node.child("x_max").child_value());
  julia->y_min = stod(julia_node.child("y_min").child_value());
  julia->y_max = stod(julia_node.child("y_max").child_value());
  julia->cx = stod(julia_node.child("cx").child_value());
  julia->cy = stod(julia_node.child("cy").child_value());
  julia->max_iterations = stoi(julia_node.child("max_iterations").child_value());
  julia->color_base = stoi(julia_node.child("color_base").child_value());
  julia->output_file = join_path(config->output_directory, julia_node.child("output_file").child_value());
  config->julia = julia;

  return config;
}
