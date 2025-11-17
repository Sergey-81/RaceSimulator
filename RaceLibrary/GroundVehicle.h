#pragma once
#include "RaceExports.h"
#include "Vehicle.h"
#include <cmath>

class RACE_API GroundVehicle : public Vehicle {
protected:
    double driveTime;

public:
    GroundVehicle(const std::string& name, double speed, double driveTime)
        : Vehicle(name, speed), driveTime(driveTime) {
    }

    virtual double getRestTime(int restCount) const = 0;

    double calculateTime(double distance) const override {
        double totalTravelTime = distance / speed;
        double currentTime = 0;
        double totalTime = 0;
        int restCount = 0;

        while (currentTime < totalTravelTime) {
            double timeUntilRest = driveTime;
            if (currentTime + timeUntilRest > totalTravelTime) {
                timeUntilRest = totalTravelTime - currentTime;
            }

            currentTime += timeUntilRest;
            totalTime += timeUntilRest;

            if (currentTime < totalTravelTime) {
                restCount++;
                double rest = getRestTime(restCount);
                totalTime += rest;
            }
        }

        return totalTime;
    }
};