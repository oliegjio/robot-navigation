#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <utility>

namespace shape {

    std::vector<std::pair<double, double>> make_rectangle(int width, int height);
    std::vector<std::pair<double, double>> make_circle(int radius);

}

#endif // SHAPE_H