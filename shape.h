#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <utility>
#include <map>
#include <tuple>
#include <GL/glu.h>

typedef int pair_type;
typedef std::pair<pair_type, pair_type> pair;

typedef std::vector<pair> vector1;
typedef std::vector<std::vector<pair>> vector2;

typedef GLfloat color_type;
typedef std::tuple<color_type, color_type, color_type> color;

typedef std::map<vector1, color> group1;
typedef std::map<vector2, color> group2;

typedef std::pair<vector1, color> shape1;
typedef std::pair<vector2, color> shape2;

namespace shape {

    vector1 make_rectangle(int width, int height);
    vector1 make_rectangle(int x, int y, int width, int height);
    vector1 make_circle(int radius);
    vector1 make_circle(int x, int y, int radius);
    
    void draw(const vector1 &shape);
    void draw(const vector1 &shape, GLfloat r, GLfloat g, GLfloat b);
    void draw(const group1 &shapes);

    void rotate(vector1 &shape, float angle);
    void translate(vector1 &shape, int x, int y);

    vector1 vectors_from_group1(group1 group);

    pair get_center(const vector1 &shape);
    vector1 vectors_from_center(const vector1 &shape);
    vector1 minkowski_sum(const vector1 &from, const vector1 &to);
    vector1 minkowski_sum_(const vector1 &from, const vector1 &to);

}

#endif // SHAPE_H
