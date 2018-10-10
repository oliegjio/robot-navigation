#include "shape.h"

#include <cmath>

std::vector<std::pair<double, double>> shape::make_rectangle(int width, int height) {

    std::vector<std::pair<double, double>> rectangle;

    for (double i = 0; i < width; i++) {
        for (double j = 0; j < height; j++) {
            rectangle.push_back(std::pair<double, double>(i , j));
        }
    }

    return rectangle;
}

std::vector<std::pair<double, double>> shape::make_circle(int radius) {

    std::vector<std::pair<double, double>> circle;

    for (double i = -radius; i < radius; i++) {
        for (double j = -radius; j < radius; j++) {
            if (i < std::sqrt(radius - std::pow(j, 2)) &&
                j < std::sqrt(radius - std::pow(i, 2)) &&
                radius < std::pow(i, 2) + std::pow(j , 2)) {
                circle.push_back(std::pair<double, double>(i, j));
            }
        }
    }

    return circle;
}