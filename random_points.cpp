#include "random_points.h"

#include "random.h"

vector1 random_points::in_bounds(pair p1, pair p2, int number) {
    vector1 result;
    result.reserve(number);
    for (int i = 0; i < number; i++) {
        int x = random(p1.first, p2.first);
        int y = random(p1.second, p2.second);
        if ((x > p1.first && y > p1.second) || (x < p2.first && y < p2.second)) {
            result.push_back(pair(x, y));
        }
    }
    return result;
}