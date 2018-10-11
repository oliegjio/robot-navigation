#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <utility>
#include <GL/glu.h>

typedef int pair_type;
typedef std::pair<pair_type, pair_type> pair;
typedef std::vector<pair> vector1;
typedef std::vector<std::vector<pair>> vector2;

namespace shape {

    vector1 make_rectangle(int width, int height);
    vector1 make_rectangle(int x, int y, int width, int height);
    vector1 make_circle(int radius);
    vector1 make_circle(int x, int y, int radius);
    
    void draw(vector1 shape);
    void draw(vector1 shape, GLfloat r, GLfloat g, GLfloat b);

    void rotate(vector1 &shape, float angle);
    void translate(vector1 &shape, int x, int y);

    pair get_center(const vector1 &shape);
    vector1 vectors_from_center(const vector1 &shape);
    vector1 minkowski_sum(const vector1 &from, const vector1 &to);
    vector1 minkowski_sum_(const vector1 &from, const vector1 &to);

}

#endif // SHAPE_H
