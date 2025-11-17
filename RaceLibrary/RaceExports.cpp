#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "RaceExports.h"
#include "Camel.h"
#include "FastCamel.h"
#include "Centaur.h"
#include "AllTerrainBoots.h"
#include "MagicCarpet.h"
#include "Eagle.h"
#include "Broom.h"
#include <cstring>

extern "C" {
    RACE_API void* createCamel() { return new Camel(); }
    RACE_API void* createFastCamel() { return new FastCamel(); }
    RACE_API void* createCentaur() { return new Centaur(); }
    RACE_API void* createAllTerrainBoots() { return new AllTerrainBoots(); }
    RACE_API void* createMagicCarpet() { return new MagicCarpet(); }
    RACE_API void* createEagle() { return new Eagle(); }
    RACE_API void* createBroom() { return new Broom(); }

    RACE_API void deleteVehicle(void* vehicle) {
        delete static_cast<Vehicle*>(vehicle);
    }

    RACE_API const char* getVehicleName(void* vehicle) {
        std::string name = static_cast<Vehicle*>(vehicle)->getName();
        char* result = new char[name.length() + 1];
        strcpy(result, name.c_str());
        return result;
    }

    RACE_API double calculateVehicleTime(void* vehicle, double distance) {
        return static_cast<Vehicle*>(vehicle)->calculateTime(distance);
    }
}