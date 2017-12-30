#pragma once
#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Eigen;

const size_t width = 640;
const size_t height = 480;

typedef Vector3f RGB;
const RGB white(1, 1, 1);
const RGB black(0, 0, 0);
const RGB red(1, 0, 0);
const RGB green(0, 1, 0);
const RGB blue(0, 0, 1);

enum Mode {sweep, box, wire, numOfMode};
Mode mode = sweep;
bool update = true;

// longitude 经度, latidude 纬度
float lng = 0, lat = 0;
float scale = 0.8;

Vector3f light(0, 0, 1);