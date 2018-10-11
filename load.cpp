#include "load.h"

#include <fstream>

points::point_vector load::map(const char *path) {
    std::ifstream file;
    file.open(path);
    points::point_vector map;
    // TODO.
    file.close();
    return map;
}


points::point_vector load::room_preset() {
    points::point_vector room;

    auto top_wall = points::rectangle(0, 399, 400, 1);
    room.insert(room.end(), top_wall.begin(), top_wall.end());

    auto bottom_wall = points::rectangle(0, 0, 400, 1);
    room.insert(room.end(), bottom_wall.begin(), bottom_wall.end());

    auto left_wall = points::rectangle(0, 1, 1, 398);
    room.insert(room.end(), left_wall.begin(), left_wall.end());

    auto right_wall = points::rectangle(399, 1, 1, 398);
    room.insert(room.end(), right_wall.begin(), right_wall.end());

    auto rectangle = points::rectangle(280, 100, 40, 150);
    room.insert(room.end(), rectangle.begin(), rectangle.end());

    auto square = points::rectangle(70, 70, 60, 60);
    room.insert(room.end(), square.begin(), square.end());

    auto circle = points::circle(150, 250, 50);
    room.insert(room.end(), circle.begin(), circle.end());

    return room;
}
