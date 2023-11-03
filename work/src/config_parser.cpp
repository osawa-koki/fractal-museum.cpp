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
    mandelbrot->color_hue_base = stoi(mandelbrot_node.child("color_hue_base").child_value());
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
  julia->color_hue_base = stoi(julia_node.child("color_hue_base").child_value());
  julia->output_file = join_path(config->output_directory, julia_node.child("output_file").child_value());
  config->julia = julia;

  pugi::xml_node tricorn_node = config_node.child("tricorn");
  Tricorn* tricorn = new Tricorn();
  tricorn->width = width;
  tricorn->height = height;
  tricorn->x_min = stod(tricorn_node.child("x_min").child_value());
  tricorn->x_max = stod(tricorn_node.child("x_max").child_value());
  tricorn->y_min = stod(tricorn_node.child("y_min").child_value());
  tricorn->y_max = stod(tricorn_node.child("y_max").child_value());
  tricorn->threshold = stoi(tricorn_node.child("threshold").child_value());
  tricorn->max_iterations = stoi(tricorn_node.child("max_iterations").child_value());
  tricorn->color_hue_base = stoi(tricorn_node.child("color_hue_base").child_value());
  tricorn->output_file = join_path(config->output_directory, tricorn_node.child("output_file").child_value());
  config->tricorn = tricorn;

  pugi::xml_node burning_ship_node = config_node.child("burning_ship");
  BurningShip* burning_ship = new BurningShip();
  burning_ship->width = width;
  burning_ship->height = height;
  burning_ship->x_min = stod(burning_ship_node.child("x_min").child_value());
  burning_ship->x_max = stod(burning_ship_node.child("x_max").child_value());
  burning_ship->y_min = stod(burning_ship_node.child("y_min").child_value());
  burning_ship->y_max = stod(burning_ship_node.child("y_max").child_value());
  burning_ship->threshold = stoi(burning_ship_node.child("threshold").child_value());
  burning_ship->max_iterations = stoi(burning_ship_node.child("max_iterations").child_value());
  burning_ship->color_hue_base = stoi(burning_ship_node.child("color_hue_base").child_value());
  burning_ship->output_file = join_path(config->output_directory, burning_ship_node.child("output_file").child_value());
  config->burning_ship = burning_ship;

  pugi::xml_node barnsley_fern_node = config_node.child("barnsley_fern");
  BarnsleyFern* barnsley_fern = new BarnsleyFern();
  barnsley_fern->width = width;
  barnsley_fern->height = height;
  barnsley_fern->size = stod(barnsley_fern_node.child("size").child_value());
  barnsley_fern->start_x = stod(barnsley_fern_node.child("start_x").child_value());
  barnsley_fern->start_y = stod(barnsley_fern_node.child("start_y").child_value());
  barnsley_fern->zoom = stod(barnsley_fern_node.child("zoom").child_value());
  barnsley_fern->max_iterations = stoi(barnsley_fern_node.child("max_iterations").child_value());
  barnsley_fern->color_hex = stoi(barnsley_fern_node.child("color_hex").child_value(), nullptr, 16);
  barnsley_fern->background_color_hex = stoi(barnsley_fern_node.child("background_color_hex").child_value(), nullptr, 16);
  barnsley_fern->output_file = join_path(config->output_directory, barnsley_fern_node.child("output_file").child_value());
  config->barnsley_fern = barnsley_fern;

  pugi::xml_node pythagoras_tree_node = config_node.child("pythagoras_tree");
  PythagorasTree* pythagoras_tree = new PythagorasTree();
  pythagoras_tree->width = width;
  pythagoras_tree->height = height;
  pythagoras_tree->color_hue_start = stoi(pythagoras_tree_node.child("color_hue_start").child_value());
  pythagoras_tree->color_hue_end = stoi(pythagoras_tree_node.child("color_hue_end").child_value());
  pythagoras_tree->background_color_hex = stoi(pythagoras_tree_node.child("background_color_hex").child_value(), nullptr, 16);
  pythagoras_tree->size = stoi(pythagoras_tree_node.child("size").child_value());
  pythagoras_tree->degree = stoi(pythagoras_tree_node.child("degree").child_value());
  pythagoras_tree->depth = stoi(pythagoras_tree_node.child("depth").child_value());
  pythagoras_tree->left = stof(pythagoras_tree_node.child("left").child_value());
  pythagoras_tree->bottom = stof(pythagoras_tree_node.child("bottom").child_value());
  pythagoras_tree->output_file = join_path(config->output_directory, pythagoras_tree_node.child("output_file").child_value());
  config->pythagoras_tree = pythagoras_tree;

  return config;
}
