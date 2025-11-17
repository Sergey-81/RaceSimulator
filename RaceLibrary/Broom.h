#pragma once
#include "RaceExports.h" 
#include "AirVehicle.h"

class RACE_API Broom : public AirVehicle {
public:
    Broom() : AirVehicle("Метла", 20) {}

    double getDistanceReduction(double distance) const override {
        int reduction = static_cast<int>(distance / 1000);
        return (reduction > 0) ? reduction : 0;
    }
};