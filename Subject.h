//
//  Subject.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-24.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <vector>
// the pure virtual class used for making a boardDisplay
class Observer;
class Board;

class Subject {
protected:
    std::vector<Observer *> observers;
public:
    virtual void attach(Observer *ob) = 0;
    virtual void notifyobservers() = 0;
    ~Subject() {}
};

#endif /* Subject_hpp */

