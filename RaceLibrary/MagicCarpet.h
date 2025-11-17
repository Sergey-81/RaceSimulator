#pragma once
#include "RaceExports.h" 
#include "AirVehicle.h"

class RACE_API MagicCarpet : public AirVehicle {
public:
    MagicCarpet() : AirVehicle("Ковёр-самолёт", 10) {}

    double getDistanceReduction(double distance) const override {
        if (distance < 1000) return 0;
        if (distance < 5000) return 3;
        if (distance < 10000) return 10;
        return 5;
    }
};