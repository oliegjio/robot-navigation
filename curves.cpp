#include "curves.h"

#include <cstdio>

#define PRECISION 0.0001

static points::point_vector get_bazier_curve(const points::point &point1, const points::point &point2, const points::point &point3) {
    points::point_vector result;
    result.reserve(static_cast<size_t>(1 / PRECISION));
    float t = 0;
    float dt = PRECISION;
    while (t < 1) {
        float p0x = static_cast<float>(point1.first);
        float p0y = static_cast<float>(point1.second);
        float p1x = static_cast<float>(point2.first);
        float p1y = static_cast<float>(point2.second);
        float p2x = static_cast<float>(point3.first);
        float p2y = static_cast<float>(point3.second);

        float b0x = p0x + (p1x - p0x) * t;
        float b0y = p0y + (p1y - p0y) * t;
        float b1x = p1x + (p2x - p1x) * t;
        float b1y = p1y + (p2y - p1y) * t;

        float cx = b0x + (b1x - b0x) * t;
        float cy = b0y + (b1y - b0y) * t;

        result.push_back(points::point(cx, cy));
        t += dt;
    }
    return result;
}

points::point_vector curves::bazier(const points::point_vector &points) {
    points::point_vector result;
    if (points.size() < 2) return result;
    result.reserve((points.size() - 2) * static_cast<size_t>(1 / PRECISION));
    for (size_t i = 1; i < points.size() - 1; i++) {
        auto midpoint1 = (points[i - 1] + points[i]) / points::point(2, 2);
        auto midpoint2 = (points[i] + points[i + 1]) / points::point(2, 2);
        auto curve = get_bazier_curve(midpoint1, points[i], midpoint2);
        result.insert(result.end(), curve.begin(), curve.end());
    }
    return result;
}
