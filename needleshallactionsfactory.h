#ifndef NEEDLESHALLACTIONSFACTORY_H
#define NEEDLESHALLACTIONSFACTORY_H

#include <string>
class Action;

class NeedlesHallActionsFactory{
    public:
        static Action * createAction(int money); // returns the action we want
};

#endif
