#ifndef LOAD_H
#define LOAD_H

#include "points.h"

namespace load {

    points::point_vector map(const char *path);
    points::point_vector room_preset();
    
}

#endif // LOAD_H