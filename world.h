#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <utility>
#include "shape.h"

namespace world {

    vector1 make_room_1(int room_width, int room_height);
    vector1 make_room_2(int room_width, int room_height);

    namespace room_2 {
        
        vector1 make_walls();
        vector1 make_rectangle();
        vector1 make_square();
        vector1 make_circle();

    }
}

#endif // WORLD_H