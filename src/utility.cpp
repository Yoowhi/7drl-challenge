#include <cstddef>
#include <cstring>
#include "libtcod.hpp"
#include "utility.hpp"

char* concatenate(const char* prefix, const char* suffix) {
    size_t newLength = strlen(prefix) + strlen(suffix) + 1;
    char* result = new char[newLength];
    strcpy(result, prefix);
    strcat(result, suffix);
    return result;
}

int rnd(int from, int to) {
    TCODRandom* rng = TCODRandom::getInstance();
    return rng->getInt(from, to);
}

int rnd(int from, int to, int mean) {
    TCODRandom* rng = TCODRandom::getInstance();
    return rng->getInt(from, to, mean);
}

tcod::ColorRGB multiplyColor(const tcod::ColorRGB color, float factor) {
    return tcod::ColorRGB{(uint8_t)(color.r * factor), (uint8_t)(color.g * factor), (uint8_t)(color.b * factor)};
}
