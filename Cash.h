//
//  Cash.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-22.
//

#ifndef Cash_hpp
#define Cash_hpp
#include "Asset.h"

class Cash: public Asset {
public:
    Cash(Player *owner, bool isOwed, int value): Asset{owner, isOwed,value} {}
    void trade(Asset *other) override;
};

#endif /* Cash_hpp */
