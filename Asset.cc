#include "Asset.h"

Player* Asset::getOwner() {
    return owner;
}

void Asset::setOwner(Player* p) {
    owner = p;
    isOwned = true;
}

bool Asset::checkOwned() {
    return isOwned;
}

int Asset::getValue() {
    return value;
}
