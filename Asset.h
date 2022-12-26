//
//  Asset.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-22.
//

#ifndef Asset_hpp
#define Asset_hpp

class Player;

// abstract base class "Asset"
class Asset {
protected:
    Player *owner;
    bool isOwned;
    int value;
public:
    Asset(Player *owner, bool isOwned, int value): owner{owner}, isOwned{isOwned}, value{value} {}
    Player *getOwner();
    void setOwner(Player *p);
    bool checkOwned();
    int getValue();
    virtual void trade(Asset *other) = 0;
    virtual ~Asset() = default;
};

#endif /* Asset_hpp */
