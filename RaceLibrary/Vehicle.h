#pragma once
#pragma warning(disable : 4251)

#include "RaceExports.h"
#include <string>

class RACE_API Vehicle {
protected:
    std::string name;
    double speed;

public:
    Vehicle(const std::string& vehicleName, double vehicleSpeed)
        : name(vehicleName), speed(vehicleSpeed) {
    }

    virtual ~Vehicle() = default;

    virtual double calculateTime(double distance) const = 0;

    std::string getName() const {
        return name;
    }

    double getSpeed() const {
        return speed;
    }
};