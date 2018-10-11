#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <utility>

namespace shape {

    std::vector<std::pair<int, int>> make_rectangle(int width, int height);
    std::vector<std::pair<int, int>> make_rectangle(int x, int y, int width, int height);
    std::vector<std::pair<int, int>> make_circle(int radius);
    std::vector<std::pair<int, int>> make_circle(int x, int y, int radius);
    
    void draw(std::vector<std::pair<int, int>> shape);

    void rotate(std::vector<std::pair<int, int>> &shape, float angle);
    void translate(std::vector<std::pair<int, int>> &shape, int x, int y);

    std::pair<int, int> get_center(const std::vector<std::pair<int, int>> &shape);
    std::vector<std::pair<int, int>> vectors_from_center(const std::vector<std::pair<int, int>> &shape);
    std::vector<std::pair<int, int>> minkowski_sum(const std::vector<std::pair<int, int>> &from, const std::vector<std::pair<int, int>> &to);

}

#endif // SHAPE_H