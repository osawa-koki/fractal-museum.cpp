#ifndef FUNCTION_HPP
#define FUNCTION_HPP

using namespace std;

#include "interface.hpp"
#include "config.hpp"

RGB *hsl_to_rgb(HSL *hsl);
Config *config_parser();
string join_path(string directory, string filename);

#endif
