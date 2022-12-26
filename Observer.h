//
//  Observer.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-24.
//

#ifndef Observer_hpp
#define Observer_hpp

class Subject;
class Board;

class Observer {
public:
    Subject *observered_obj;
    Observer(Subject *sub);
    virtual void notify(Board *whoNotified) = 0;
    virtual ~Observer() = default;
};

#endif /* Observer_hpp */

