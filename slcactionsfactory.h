#ifndef SLCACTIONSFACTORY_H
#define SLCACTIONSFACTORY_H

#include "action.h"
#include <string>

class SLCActionsFactory{
    public:
        static Action * createAction(std::string position); // returns the action we want
};

#endif
