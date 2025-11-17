#pragma once
#include "RaceExports.h" 
#include "GroundVehicle.h"

class RACE_API FastCamel : public GroundVehicle {
public:
    FastCamel() : GroundVehicle("Верблюд-быстроход", 40, 10) {}

    double getRestTime(int restCount) const override {
        if (restCount == 1) return 5;
        if (restCount == 2) return 6.5;
        return 8;
    }
};