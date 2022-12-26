#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ownablefactory.h"
#include "ownable.h"

OwnableFactory::OwnableFactory() {
    map<string, vector<int>> monopoly;
    map<string, OwnableType> monotype;

    monopoly["AL"] = vector<int> {40, 2};
    monopoly["ML"] = vector<int> {60, 4};
    monopoly["ECH"] = vector<int> {100, 6};
    monopoly["PAS"] = vector<int> {100, 6};
    monopoly["HH"] = vector<int> {120, 8};
    monopoly["RCH"] = vector<int> {140, 10};
    monopoly["DWE"] = vector<int> {140, 10};
    monopoly["CPH"] = vector<int> {160, 12};
    monopoly["LHI"] = vector<int> {180, 14};
    monopoly["BMH"] = vector<int> {180, 14};
    monopoly["OPT"] = vector<int> {200, 16};
    monopoly["EV1"] = vector<int> {220, 18};
    monopoly["EV2"] = vector<int> {220, 18};
    monopoly["EV3"] = vector<int> {240, 20};
    monopoly["PHYS"] = vector<int> {260, 22};
    monopoly["B1"] = vector<int> {260, 22};
    monopoly["B2"] = vector<int> {280, 24};
    monopoly["EIT"] = vector<int> {300, 26};
    monopoly["ESC"] = vector<int> {300, 26};
    monopoly["C2"] = vector<int> {320, 28};
    monopoly["MC"] = vector<int> {350, 35};
    monopoly["DC"] = vector<int> {400, 50};
    monopoly["MKV"] = vector<int> {200, 25};
    monopoly["UWP"] = vector<int> {200, 25};
    monopoly["V1"] = vector<int> {200, 25};
    monopoly["REV"] = vector<int> {200, 25};
    monopoly["PAC"] = vector<int> {150, 0};
    monopoly["CIF"] = vector<int> {150, 0};

    monotype["AL"] = OwnableType::Improvable;
    monotype["ML"] = OwnableType::Improvable;
    monotype["ECH"] = OwnableType::Improvable;
    monotype["PAS"] = OwnableType::Improvable;
    monotype["HH"] = OwnableType::Improvable;
    monotype["RCH"] = OwnableType::Improvable;
    monotype["DWE"] = OwnableType::Improvable;
    monotype["CPH"] = OwnableType::Improvable;
    monotype["LHI"] = OwnableType::Improvable;
    monotype["BMH"] = OwnableType::Improvable;
    monotype["OPT"] = OwnableType::Improvable;
    monotype["EV1"] = OwnableType::Improvable;
    monotype["EV2"] = OwnableType::Improvable;
    monotype["EV3"] = OwnableType::Improvable;
    monotype["PHYS"] = OwnableType::Improvable;
    monotype["B1"] = OwnableType::Improvable;
    monotype["B2"] = OwnableType::Improvable;;
    monotype["EIT"] = OwnableType::Improvable;
    monotype["ESC"] = OwnableType::Improvable;
    monotype["C2"] = OwnableType::Improvable;
    monotype["MC"] = OwnableType::Improvable;
    monotype["DC"] = OwnableType::Improvable;
    monotype["MKV"] = OwnableType::Residence;
    monotype["UWP"] = OwnableType::Residence;
    monotype["V1"] = OwnableType::Residence;
    monotype["REV"] = OwnableType::Residence;
    monotype["PAC"] = OwnableType::Gym;
    monotype["CIF"] = OwnableType::Gym;

    buildinfo = monopoly;
    buildpay = monotype;
}

Ownable* OwnableFactory::createOwnable(string name, int position) {
    Ownable* myOwn = new Ownable(name, position, buildinfo[name][0], buildinfo[name][1], buildpay[name]);
    // buildinfo[name][0] gets buy price and buildinfo[name][1] gets rent price
    return myOwn;
}
