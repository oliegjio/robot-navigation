#include "delaunay.h"

#include <cstdio>
#include <list>

enum orientation {
    left = 0,
    right = 1
};

static delaunay::hull::iterator nextIter(delaunay::hull::iterator it, delaunay::hull::iterator begin, delaunay::hull::iterator end) {
    it++;
    if (it == end) {
        it = begin;
    }
    return it;
}

static delaunay::hull::iterator prevIter(delaunay::hull::iterator it, delaunay::hull::iterator begin, delaunay::hull::iterator end) {
    if (it == begin) {
        it = end;
    }
    it--;
    return it;
}

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
    auto triangle = initial_triangle(points[0], points[1], points[2]);
    result->push_back(triangle);
    auto hull = delaunay::hull();
    hull.push_back(triangle->vertices[0]);
    hull.push_back(triangle->vertices[1]);
    hull.push_back(triangle->vertices[1]);
    auto it = hull.begin();
    for (size_t i = 3; i < points.size() - 3; i++) {
        size_t node_number = 0;
        while (node_number != hull.size()) {
            orientation side = get_side(it.first, it.second, points[i]);
            if (side == orientation::right) {
                    printf("!!!\n");
//                auto new_triangle = make_triangle();
//                new_triangle->vertices();
//                result.push_back(new_triangle);
                // DELETE j elem from hull
                // ADD NEW TOP edge to the hull
                // CHECK for reverse bottom edge
                    // IF there is THEN remove reverse edge
                    // IF there is no THEN add bottom edge to the hull
                // ADD points[i] to the hull            
            }
            node_number += 1;
            it = nextIter(it, hull.begin(), hull.end());
        }
    }
    return result;
}