#include "curves.h"

points::point_vector curves::bazier(const points::point_vector &points) {
    points::point_vector result;
    float t = 0;
    float dt = 0.0001;
    while (t < 1) {
        float p0x = static_cast<float>(points[0].first);
        float p0y = static_cast<float>(points[0].second);
        float p1x = static_cast<float>(points[1].first);
        float p1y = static_cast<float>(points[1].second);
        float p2x = static_cast<float>(points[2].first);
        float p2y = static_cast<float>(points[2].second);

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