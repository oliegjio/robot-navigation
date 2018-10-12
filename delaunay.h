#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <vector>
#include <list>

#include "points.h"

namespace delaunay {

    struct triangle {
        std::vector<points::point*> *vertices;
        std::vector<triangle*> *triangles;
    };
    typedef std::vector<points::point*> vertices;
    typedef std::vector<triangle*> triangles;
    typedef std::list<std::pair<points::point*, points::point*>> hull;

    triangles *triangulate(points::point_vector &points);

}

#endif // DELAUNAY_H