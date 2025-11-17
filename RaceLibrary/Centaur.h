#pragma once
#include "RaceExports.h" 
#include "GroundVehicle.h"

class RACE_API Centaur : public GroundVehicle {
public:
    Centaur() : GroundVehicle("Кентавр", 15, 8) {}

    double getRestTime(int restCount) const override {
        return 2;
    }
};