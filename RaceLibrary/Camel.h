#pragma once
#include "RaceExports.h" 
#include "GroundVehicle.h"

class RACE_API Camel : public GroundVehicle {
public:
    Camel() : GroundVehicle("Верблюд", 10, 30) {}

    double getRestTime(int restCount) const override {
        return (restCount == 1) ? 5 : 8;
    }
};