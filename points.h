#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include <utility>
#include <GL/glu.h>

namespace points {

    typedef int point_type;
    typedef std::pair<point_type, point_type> point;
    typedef std::vector<point> point_vector;
    typedef GLfloat color_type;

    point_vector rectangle(point_type x, point_type y, point_type width, point_type height);
    point_vector circle(point_type x, point_type y, point_type radius);
    point_vector grid(point_type x1, point_type y1, point_type x2, point_type y2, float fraction);
    point_vector random(point_type x1, point_type y1, point_type x2, point_type y2, size_t number, point_type delta);
    
    void draw(const point_vector &points, color_type r = 0, color_type g = 0, color_type b = 0);

    void rotate(point_vector &points, float angle);
    void translate(point_vector &points, point_type x, point_type y);

    float distance(const point &from, const point &to);

    point center(const point_vector &points);
    point_vector center_vectors(const point_vector &points);
    point_vector minkowski(const point_vector &source, const point_vector &target);
    point_vector minkowski2(const point_vector &source, const point_vector &target);

}

points::point operator+(const points::point &left, const points::point &right);
points::point operator-(const points::point &left, const points::point &right);
points::point operator*(const points::point &left, const points::point &right);
points::point operator/(const points::point &left, const points::point &right);

#endif // POINTS_H
