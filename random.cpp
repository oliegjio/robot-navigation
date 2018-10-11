#include "random.h"

#include <cstdlib>

int random(int from, int to) {
    return from + (std::rand() % (to - from + 1));
}