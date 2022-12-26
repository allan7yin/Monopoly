#ifndef NONPROPERTIESACTIONSFACTORY_H
#define NONPROPERTIESACTIONSFACTORY_H

#include <string>
class Action;

class NonPropertiesActionsFactory{
    public:
        static Action * createAction(std::string type); // returns the action we want
};

#endif
