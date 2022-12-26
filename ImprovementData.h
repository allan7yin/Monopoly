//
//  ImprovementData.hpp
//  ur mom
//
//  Created by j446zhao on 2022-07-25.
//

#ifndef ImprovementData_hpp
#define ImprovementData_hpp

#include <string>
#include <vector>

// will read into this struct in Board, and will use it as a reference when getting price
class ImprovementData {
public:
    std::string name;
    std::string monpoly;
    int purchaseCost;
    int improvementCost;
    std::vector<int> improvedTuition;;
    
    ImprovementData() {}
};


#endif /* ImprovementData_hpp */
