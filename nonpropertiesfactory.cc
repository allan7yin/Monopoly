//
//  nonpropertiesfactory.cpp
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#include "nonpropertiesfactory.h"

#include <string>
#include "nonproperties.h"
#include "nonpropertiesactionsfactory.h"
#include "needleshall.h"
#include "slc.h"
#include "needleshall.h"

NonProperties * NonPropertiesFactory::createNonProperties(std::string type, int position){
    if(type == "SLC"){
        return new Slc{type, position};
    }
    else if(type == "NEEDLES HALL"){
        return new NeedlesHall{type, position};
    }
    else{
        return new NonProperties{type, position, NonPropertiesActionsFactory::createAction(type)};
    }
}

