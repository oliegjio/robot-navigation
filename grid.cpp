#include "grid.h"

#include <cmath>

vector1 grid::make_grid(int x1, int y1, int x2, int y2, float factor) {
    vector1 grid;
    int width = std::abs(x1 - x2);
    int height = std::abs(y1 - y2);
    int cell_width = static_cast<float>(width) * factor;
    int cell_height = static_cast<float>(height) * factor;
    for (int i = 0; i < width; i += cell_width) {
        for (int j = 0; j < height; j += cell_height) {
            grid.push_back(pair(i, j));
        }
    }
    return grid;
}