#pragma once
#include "RaceExports.h" 
#include "GroundVehicle.h"

class RACE_API AllTerrainBoots : public GroundVehicle {
public:
    AllTerrainBoots() : GroundVehicle("Ботинки-вездеходы", 6, 60) {}

    double getRestTime(int restCount) const override {
        return (restCount == 1) ? 10 : 5;
    }
};