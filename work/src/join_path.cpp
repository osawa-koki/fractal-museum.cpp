#ifndef JOIN_PATH_CPP
#define JOIN_PATH_CPP

#include <string>

using namespace std;

string join_path(string directory, string filename)
{
  string path = directory + filename;
  return path;
}

#endif
