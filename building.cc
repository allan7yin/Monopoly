#include "building.h"

Building::Building(std::string name, int position):
    name{name},
    position{position}
{}

std::string Building::getName() {
    return name;
}



