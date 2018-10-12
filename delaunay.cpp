#include "delaunay.h"

// SIDE FORMULA: d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
// If d <= 0 -> left side, otherwise -> right side

#include <cstdio>

enum orientation {
    left = 0,
    right = 1
};

static orientation get_side(const points::point &start, const points::point &end, const points::point &point) {
    return (point.first - start.first) * (end.second - start.second) - (point.second - start.second) * (end.first - start.first) <= 0 ? orientation::left : orientation::right;
}

static void sort(points::point_vector &points) {
    for (size_t i = points.size() - 1; i > 0; i--) {
        for (size_t j = 0; j < i; j++) {
            if (points[j].first > points[j + 1].first) {
                points::point swap = points[j];
                points[j] = points[j + 1];
                points[j + 1] = swap;
            }
        }
    }
}

static delaunay::triangle *make_triangle() {
    auto *result = new delaunay::triangle;
    result->vertices = new delaunay::vertices;
    result->triangles = new delaunay::triangles;
    return result;
}

static delaunay::triangle *initial_triangle(points::point &first, points::point &second, points::point &third) {
    auto *result = make_triangle();
    orientation side = get_side(first, second, third);
    if (side == orientation::left) {
        result->vertices->push_back(&first);
        result->vertices->push_back(&second);
        result->vertices->push_back(&third);
    } else {
        result->vertices->push_back(&second);
        result->vertices->push_back(&first);
        result->vertices->push_back(&third);
    }
    return result;
}

delaunay::triangles *delaunay::triangulate(points::point_vector &points) {
    if (points.size() < 3) return nullptr;
    sort(points);
    auto result = new delaunay::triangles;
    result->push_back(initial_triangle(points[0], points[1], points[2]));
    return result;
}