#pragma once
#include "RaceExports.h" 
#include "AirVehicle.h"

class RACE_API Eagle : public AirVehicle {
public:
    Eagle() : AirVehicle("Îð¸ë", 8) {}

    double getDistanceReduction(double distance) const override {
        return 6;
    }
};