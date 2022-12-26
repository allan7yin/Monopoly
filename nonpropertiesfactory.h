//
//  nonpropertiesfactory.hpp
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef nonpropertiesfactory_h
#define nonpropertiesfactory_h

class NonProperties;

#include <string>

class NonPropertiesFactory {
    public:
        static NonProperties * createNonProperties(std::string type, int position);
};

#endif /* nonpropertiesfactory_h */
