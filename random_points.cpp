#include "random_points.h"

#include "random.h"
#include <cmath>

static float distance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

vector1 random_points::in_bounds(int x1, int y1, int x2, int y2, int number, float delta) {
    vector1 result;
    result.reserve(number);
    int generated = 0;
    int distance_flag = 0;
    while (generated != number) {
        int x = random(x1, x2);
        int y = random(y1, y2);
        for (size_t i = 0; i < result.size(); i++) {
            if (distance(x, y, result[i].first, result[i].second) < delta) {
                distance_flag = 1;
                break;
            }
        }
        if (distance_flag == 0) {
            result.push_back(pair(x, y));
            generated += 1;
        }
        distance_flag = 0;
    }
    return result;
}