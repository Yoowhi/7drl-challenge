#pragma once
#include "libtcod.hpp"

char* concatenate(const char* prefix, const char* suffix);
int rnd(int from, int to);
int rnd(int from, int to, int mean);
int rnd(int from, int to, int mean);
tcod::ColorRGB multiplyColor(const tcod::ColorRGB color, float factor);
