#include "shape.h"

#include <cmath>
#include <math.h>
#include <set>

vector1 shape::make_rectangle(int width, int height) {

    vector1 rectangle;
    rectangle.reserve(width * height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            rectangle.push_back(pair(i , j));
        }
    }

    return rectangle;
}

vector1 shape::make_rectangle(int x, int y, int width, int height) {

    vector1 rectangle;
    rectangle.reserve(width * height);

    for (int i = x; i < width + x; i++) {
        for (int j = y; j < height + y; j++) {
            rectangle.push_back(pair(i, j));
        }
    }

    return rectangle;
}

vector1 shape::make_circle(int radius) {
    int diamiter = radius * 2;

    vector1 circle;
    circle.reserve(2 * diamiter * 4);

    for (int i = -diamiter; i < diamiter; i++) {
        for (int j = -diamiter; j < diamiter; j++) {
            if (i < std::sqrt(diamiter - std::pow(j, 2)) &&
                j < std::sqrt(diamiter - std::pow(i, 2)) &&
                diamiter > std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(pair(i, j));
            }
        }
    }

    return circle;
}

vector1 shape::make_circle(int x, int y, int radius) {
    int diamiter = radius * 2;

    vector1 circle;
    circle.reserve(2 * diamiter * 4);

    for (int i = -diamiter; i < diamiter; i++) {
        for (int j = -diamiter; j < diamiter; j++) {
            if (i < std::sqrt(diamiter - std::pow(j, 2)) &&
                j < std::sqrt(diamiter - std::pow(i, 2)) &&
                diamiter > std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(pair(i + x, j + y));
            }
        }
    }

    return circle;
}

void shape::draw(vector1 shape) {
    glBegin(GL_POINTS);
    for (size_t i = 0; i < shape.size(); i++) {
        glVertex2f(shape[i].first, shape[i].second);
    }
    glEnd();
}

void shape::draw(vector1 shape, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < shape.size(); i++) {
        glVertex2f(shape[i].first, shape[i].second);
    }
    glEnd();
}

pair shape::get_center(const vector1 &shape) {
    pair point(0, 0);
    unsigned long int size = shape.size();
    for (size_t i = 0; i < size; i++) {
        point.first += shape[i].first;
        point.second += shape[i].second;
    }
    point.first /= size;
    point.second /= size;
    return point;
}

vector1 shape::vectors_from_center(const vector1 &shape) {
    vector1 result;
    auto center = shape::get_center(shape);
    result.reserve(shape.size());
    for (size_t i = 0; i < shape.size(); i++) {
        result.push_back(pair(shape[i].first - center.first, shape[i].second - center.second));
    }
    return result;
}

void shape::translate(vector1 &shape, int x, int y) {
    for (size_t i = 0; i < shape.size(); i++) {
        shape[i].first += x;
        shape[i].second += y;
    }
}

void shape::rotate(vector1 &shape, float angle) {
    float cos = std::cos(angle);
    float sin = std::sin(angle);
    pair center = shape::get_center(shape);
    shape::translate(shape, -center.first, -center.second);
    for (size_t i = 0; i < shape.size(); i++) {
        shape[i].first = shape[i].first * cos - shape[i].second * sin;
        shape[i].second = shape[i].first * sin + shape[i].second * cos;
    }
    shape::translate(shape, center.first, center.second);
}

vector1 shape::minkowski_sum(const vector1 &from, const vector1 &to) {
    std::set<std::pair<int, int>> set;
    auto centers = shape::vectors_from_center(from);
    for (size_t i = 0; i < to.size(); i++) {
        for (size_t j = 0; j < centers.size(); j++) {
            set.insert(pair(to[i].first + centers[j].first, to[i].second + centers[j].second));
        }
    }
    vector1 result(set.begin(), set.end());
    return result;
}
