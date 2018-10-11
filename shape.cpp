#include "shape.h"

#include <GL/glu.h>
#include <cmath>
#include <math.h>

std::vector<std::pair<int, int>> shape::make_rectangle(int width, int height) {

    std::vector<std::pair<int, int>> rectangle;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            rectangle.push_back(std::pair<int, int>(i , j));
        }
    }

    return rectangle;
}

std::vector<std::pair<int, int>> shape::make_rectangle(int x, int y, int width, int height) {

    std::vector<std::pair<int, int>> rectangle;

    for (int i = x; i < width + x; i++) {
        for (int j = y; j < height + y; j++) {
            rectangle.push_back(std::pair<int, int>(i, j));
        }
    }

    return rectangle;
}

std::vector<std::pair<int, int>> shape::make_circle(int radius) {

    std::vector<std::pair<int, int>> circle;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {
            if (i < std::sqrt(radius - std::pow(j, 2)) &&
                j < std::sqrt(radius - std::pow(i, 2)) &&
                radius > std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(std::pair<int, int>(i, j));
            }
        }
    }

    return circle;
}

std::vector<std::pair<int, int>> shape::make_circle(int x, int y, int radius) {

    std::vector<std::pair<int, int>> circle;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {
            if (i < std::sqrt(radius - std::pow(j, 2)) &&
                j < std::sqrt(radius - std::pow(i, 2)) &&
                radius > std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(std::pair<int, int>(i + x, j + y));
            }
        }
    }

    return circle;
}

void shape::draw(std::vector<std::pair<int, int>> shape) {
    glBegin(GL_POINTS);
    for (int i = 0; i < shape.size(); i++) {
        glVertex2f(shape[i].first, shape[i].second);
    }
    glEnd();
}

std::pair<int, int> shape::get_center(const std::vector<std::pair<int, int>> &shape) {
    std::pair<int, int> point(0, 0);
    unsigned long int size = shape.size();
    for (int i = 0; i < size; i++) {
        point.first += shape[i].first;
        point.second += shape[i].second;
    }
    point.first /= size;
    point.second /= size;
    return point;
}

std::vector<std::pair<int, int>> shape::vectors_from_center(const std::vector<std::pair<int, int>> &shape) {
    std::vector<std::pair<int, int>> result;
    auto center = shape::get_center(shape);
    for (int i = 0; i < shape.size(); i++) {
        result.push_back(std::pair<int, int>(shape[i].first - center.first, shape[i].second - center.second));
    }
    return result;
}

void shape::translate(std::vector<std::pair<int, int>> &shape, int x, int y) {
    for (int i = 0; i < shape.size(); i++) {
        shape[i].first += x;
        shape[i].second += y;
    }
}

void shape::rotate(std::vector<std::pair<int, int>> &shape, float angle) {
    float cos = std::cos(angle);
    float sin = std::sin(angle);
    std::pair<int, int> center = shape::get_center(shape);
    shape::translate(shape, -center.first, -center.second);
    for (int i = 0; i < shape.size(); i++) {
        shape[i].first = shape[i].first * cos - shape[i].second * sin;
        shape[i].second = shape[i].first * sin + shape[i].second * cos;
    }
    shape::translate(shape, center.first, center.second);
}

std::vector<std::pair<int, int>> shape::minkowski_sum(const std::vector<std::pair<int, int>> &from, const std::vector<std::pair<int, int>> &to) {
    std::vector<std::pair<int, int>> result;
    auto centers = shape::vectors_from_center(from);
    for (int i = 0; i < to.size(); i++) {
        for (int j = 0; j < centers.size(); j++) {
            result.push_back(std::pair<int, int>(to[i].first + centers[j].first, to[i].second + centers[j].second));
        }
    }
    return result;
}
