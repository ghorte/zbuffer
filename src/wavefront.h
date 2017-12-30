#pragma once
#include "global.h"
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <locale>

// trim from end (in place)
static inline std::string rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
    return !(ch == '/');
  }).base(), s.end());
  return s;
}

vector<vector<string> > parseText(const string& file) {
  ifstream input(file);
  if (input.fail())
    throw runtime_error("open " + file + " fail.");
  string buffer;

  vector<vector<string> >lines;
  for (size_t i = 1; getline(input, buffer); ++i) {
    istringstream iss(buffer);
    vector<string> tokens{//split
      istream_iterator<string>{iss},
      istream_iterator<string>{}
    };
    if (tokens.size() > 0) //trim blank and '/'
      lines.push_back(tokens);
  }
  return lines;
}

class Mesh {
public:
  vector<vector<Vector3f> >polygons;
  Mesh(const string& filename) {
    vector<vector<string> >lines = parseText(filename);
    vector<vector<string> >pts_txt, idxs_txt;
    for (size_t i = 0; i < lines.size(); ++i) {
      if (lines[i][0] == "v")
        pts_txt.push_back(lines[i]);
      if (lines[i][0] == "f")
        idxs_txt.push_back(lines[i]);
    }

    // store value from text
    MatrixXf pts(3, pts_txt.size());
    for (size_t i = 0; i < pts_txt.size(); ++i)
      for (size_t j = 0; j < 3; ++j)
        pts(j, i) = stof(pts_txt[i][j + 1]);

    tris.resize(3, idxs_txt.size() * 3);
    for (size_t i = 0; i < idxs_txt.size(); ++i) {
      for (size_t j = 0; j < 3; ++j) {
        int index = stoi(rtrim(idxs_txt[i][j + 1])) - 1;
        tris.col(3 * i + j) = pts.col(index);
      }
    }
  }
};
