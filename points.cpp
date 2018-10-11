#include "points.h"

#include <cmath>
#include <math.h>
#include <set>

#include "rnd.h"

points::point_vector points::rectangle(points::point_type x, points::point_type y, points::point_type width, points::point_type height) {
    points::point_vector rectangle;
    rectangle.reserve(static_cast<size_t>(width * height));

    for (points::point_type i = x; i < width + x; i++) {
        for (points::point_type j = y; j < height + y; j++) {
            rectangle.push_back(points::point(i, j));
        }
    }

    return rectangle;
}

points::point_vector points::circle(points::point_type x, points::point_type y, points::point_type radius) {
    points::point_vector circle;
    circle.reserve(static_cast<size_t>(M_PI * std::pow(radius, 2)));
    points::point_type diamiter = radius * 2;

    for (points::point_type i = -diamiter; i < diamiter; i++) {
        for (points::point_type j = -diamiter; j < diamiter; j++) {
            if (i < std::sqrt(diamiter - std::pow(j, 2)) &&
                j < std::sqrt(diamiter - std::pow(i, 2)) &&
                diamiter > std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(points::point(i + x, j + y));
            }
        }
    }

    return circle;
}

points::point_vector points::grid(points::point_type x1,
                                  points::point_type y1,
                                  points::point_type x2,
                                  points::point_type y2,
                                  float fraction) {
    points::point_vector grid;
    points::point_type width = std::abs(x1 - x2);
    points::point_type height = std::abs(y1 - y2);
    points::point_type cell_width = static_cast<float>(width) * fraction;
    points::point_type cell_height = static_cast<float>(height) * fraction;
    for (points::point_type i = 0; i < width; i += cell_width) {
        for (points::point_type j = 0; j < height; j += cell_height) {
            grid.push_back(points::point(i, j));
        }
    }
    return grid;
}

points::point_vector points::random(points::point_type x1,
                                    points::point_type y1,
                                    points::point_type x2,
                                    points::point_type y2,
                                    size_t number,
                                    points::point_type delta) {
    points::point_vector result;
    result.reserve(number);
    size_t generated = 0;
    int distance_flag = 0;
    while (generated != number) {
        int x = rnd::in_range(x1, x2);
        int y = rnd::in_range(y1, y2);
        for (size_t i = 0; i < result.size(); i++) {
            if (points::distance(points::point(x, y), result[i]) < delta) {
                distance_flag = 1;
                break;
            }
        }
        if (distance_flag == 0) {
            result.push_back(points::point(x, y));
            generated += 1;
        }
        distance_flag = 0;
    }
    return result;
}

void points::draw(const points::point_vector &points, points::color_type r, points::color_type g, points::color_type b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < points.size(); i++) {
        glVertex2f(points[i].first, points[i].second);
    }
    glEnd();
}

points::point points::center(const points::point_vector &points) {
    points::point point(0, 0);
    size_t size = points.size();
    for (size_t i = 0; i < size; i++) {
        point.first += points[i].first;
        point.second += points[i].second;
    }
    point.first /= size;
    point.second /= size;
    return point;
}

points::point_vector points::center_vectors(const points::point_vector &points) {
    points::point_vector result;
    result.reserve(points.size());
    points::point center = points::center(points);
    for (size_t i = 0; i < points.size(); i++) {
        result.push_back(points::point(points[i].first - center.first, points[i].second - center.second));
    }
    return result;
}

void points::translate(points::point_vector &points, points::point_type x, points::point_type y) {
    for (size_t i = 0; i < points.size(); i++) {
        points[i].first += x;
        points[i].second += y;
    }
}

void points::rotate(points::point_vector &points, float angle) {
    float cos = std::cos(angle);
    float sin = std::sin(angle);
    points::point center = points::center(points);
    points::translate(points, -center.first, -center.second);
    for (size_t i = 0; i < points.size(); i++) {
        points[i].first = points[i].first * cos - points[i].second * sin;
        points[i].second = points[i].first * sin + points[i].second * cos;
    }
    points::translate(points, center.first, center.second);
}

float points::distance(const points::point &from, const points::point &to) {
    return std::sqrt(std::pow(from.first - to.first, 2) + std::pow(from.second - to.second, 2));
}

points::point_vector points::minkowski(const points::point_vector &source, const points::point_vector &target) {
    std::set<points::point> set;
    points::point_vector center_vectors = points::center_vectors(source);
    for (size_t i = 0; i < target.size(); i++) {
        for (size_t j = 0; j < center_vectors.size(); j++) {
            set.insert(points::point(target[i].first + center_vectors[j].first, target[i].second + center_vectors[j].second));
        }
    }
    points::point_vector result(set.begin(), set.end());
    return result;
}

points::point_vector points::minkowski2(const points::point_vector &source, const points::point_vector &target) {
    std::set<points::point> set;
    points::point_vector center_vectors = points::center_vectors(source);
    for (size_t i = 0; i < target.size(); i++) {
        for (size_t j = 0; j < center_vectors.size(); j++) {
            set.insert(points::point(target[i].first + center_vectors[j].first, target[i].second + center_vectors[j].second));
        }
    }
    points::point_vector result(set.begin(), set.end());
    return result;
}

