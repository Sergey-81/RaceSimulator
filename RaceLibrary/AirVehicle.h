#pragma once
#include "RaceExports.h" 
#include "Vehicle.h"

class RACE_API AirVehicle : public Vehicle {
public:
    AirVehicle(const std::string& name, double speed)
        : Vehicle(name, speed) {
    }

    virtual double getDistanceReduction(double distance) const = 0;

    double calculateTime(double distance) const override {
        double reducedDistance = distance * (1 - getDistanceReduction(distance) / 100.0);
        return reducedDistance / speed;
    }
};
