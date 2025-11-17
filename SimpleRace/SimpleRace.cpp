#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <map>
#include <windows.h>

typedef void* (*CreateVehicleFunc)();
typedef void (*DeleteVehicleFunc)(void*);
typedef const char* (*GetNameFunc)(void*);
typedef double (*CalculateTimeFunc)(void*, double);

class DLLVehicle {
private:
    void* vehiclePtr;
    DeleteVehicleFunc deleteFunc;
    GetNameFunc getNameFunc;
    CalculateTimeFunc calculateTimeFunc;

public:
    DLLVehicle(void* vehicle, DeleteVehicleFunc del,
        GetNameFunc getName, CalculateTimeFunc calcTime)
        : vehiclePtr(vehicle), deleteFunc(del),
        getNameFunc(getName), calculateTimeFunc(calcTime) {
    }

    ~DLLVehicle() {
        if (deleteFunc && vehiclePtr) {
            deleteFunc(vehiclePtr);
        }
    }

    std::string getName() const {
        return getNameFunc(vehiclePtr);
    }

    double calculateTime(double distance) const {
        return calculateTimeFunc(vehiclePtr, distance);
    }
};

enum class RaceType {
    GROUND,
    AIR,
    MIXED
};

class Race {
private:
    RaceType type;
    double distance;
    std::vector<std::shared_ptr<DLLVehicle>> vehicles;

public:
    Race(RaceType raceType, double raceDistance)
        : type(raceType), distance(raceDistance) {
    }

    bool registerVehicle(std::shared_ptr<DLLVehicle> vehicle) {
        for (const auto& v : vehicles) {
            if (v->getName() == vehicle->getName()) {
                return false;
            }
        }
        vehicles.push_back(vehicle);
        return true;
    }

    std::vector<std::pair<std::string, double>> startRace() const {
        std::vector<std::pair<std::string, double>> results;

        for (const auto& vehicle : vehicles) {
            double time = vehicle->calculateTime(distance);
            results.emplace_back(vehicle->getName(), time);
        }

        std::sort(results.begin(), results.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        return results;
    }

    RaceType getType() const { return type; }
    double getDistance() const { return distance; }
    size_t getVehicleCount() const { return vehicles.size(); }

    static std::string raceTypeToString(RaceType type) {
        switch (type) {
        case RaceType::GROUND: return "наземная";
        case RaceType::AIR: return "воздушная";
        case RaceType::MIXED: return "смешанная";
        default: return "неизвестный тип";
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    HMODULE dllHandle = LoadLibraryA("RaceLibrary.dll");
    std::cout << "DLL loaded successfully!" << std::endl;
    if (!dllHandle) {
        std::cout << "Ошибка загрузки DLL!" << std::endl;
        return 1;
    }

    auto createCamel = (CreateVehicleFunc)GetProcAddress(dllHandle, "createCamel");
    auto createFastCamel = (CreateVehicleFunc)GetProcAddress(dllHandle, "createFastCamel");
    auto createCentaur = (CreateVehicleFunc)GetProcAddress(dllHandle, "createCentaur");
    auto createBoots = (CreateVehicleFunc)GetProcAddress(dllHandle, "createAllTerrainBoots");
    auto createCarpet = (CreateVehicleFunc)GetProcAddress(dllHandle, "createMagicCarpet");
    auto createEagle = (CreateVehicleFunc)GetProcAddress(dllHandle, "createEagle");
    auto createBroom = (CreateVehicleFunc)GetProcAddress(dllHandle, "createBroom");

    auto deleteVehicle = (DeleteVehicleFunc)GetProcAddress(dllHandle, "deleteVehicle");
    auto getName = (GetNameFunc)GetProcAddress(dllHandle, "getVehicleName");
    auto calcTime = (CalculateTimeFunc)GetProcAddress(dllHandle, "calculateVehicleTime");

    std::cout << "Checking functions..." << std::endl;
    if (!createCamel) std::cout << "createCamel not found!" << std::endl;
    if (!createFastCamel) std::cout << "createFastCamel not found!" << std::endl;
    if (!createCentaur) std::cout << "createCentaur not found!" << std::endl;
    if (!createBoots) std::cout << "createBoots not found!" << std::endl;
    if (!createCarpet) std::cout << "createCarpet not found!" << std::endl;
    if (!createEagle) std::cout << "createEagle not found!" << std::endl;
    if (!createBroom) std::cout << "createBroom not found!" << std::endl;
    if (!deleteVehicle) std::cout << "deleteVehicle not found!" << std::endl;
    if (!getName) std::cout << "getName not found!" << std::endl;
    if (!calcTime) std::cout << "calcTime not found!" << std::endl;
    std::cout << "All functions found: " << (createCamel && createFastCamel && createCentaur && createBoots && createCarpet && createEagle && createBroom && deleteVehicle && getName && calcTime) << std::endl;


    std::vector<std::shared_ptr<DLLVehicle>> allVehicles;

    if (createCamel && createFastCamel && createCentaur && createBoots &&
        createCarpet && createEagle && createBroom && deleteVehicle && getName && calcTime) {

        allVehicles = {
            std::make_shared<DLLVehicle>(createCamel(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createFastCamel(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createCentaur(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createBoots(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createCarpet(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createEagle(), deleteVehicle, getName, calcTime),
            std::make_shared<DLLVehicle>(createBroom(), deleteVehicle, getName, calcTime)
        };
    }
    std::cout << "Created " << allVehicles.size() << " vehicles" << std::endl;
    for (const auto& vehicle : allVehicles) {
        std::cout << "Vehicle name: '" << vehicle->getName() << "'" << std::endl;
    }

    std::map<std::string, std::shared_ptr<DLLVehicle>> vehicleMap;
    for (const auto& vehicle : allVehicles) {
        vehicleMap[vehicle->getName()] = vehicle;
    }

    bool running = true;

    while (running) {
        std::cout << "\n=== СИМУЛЯТОР ГОНОК ===" << std::endl;
        std::cout << "1. Наземная гонка" << std::endl;
        std::cout << "2. Воздушная гонка" << std::endl;
        std::cout << "3. Смешанная гонка" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите тип гонки: ";

        int choice;
        std::cin >> choice;

        RaceType raceType;
        switch (choice) {
        case 1: raceType = RaceType::GROUND; break;
        case 2: raceType = RaceType::AIR; break;
        case 3: raceType = RaceType::MIXED; break;
        case 0: running = false; continue;
        default:
            std::cout << "Неверный выбор!" << std::endl;
            continue;
        }

        std::cout << "Введите дистанцию гонки: ";
        double distance;
        std::cin >> distance;

        Race race(raceType, distance);
        bool inRaceMenu = true;

        while (inRaceMenu) {
            std::cout << "\nГонка: " << Race::raceTypeToString(race.getType())
                << ", дистанция: " << race.getDistance()
                << " км, зарегистрировано: " << race.getVehicleCount() << std::endl;

            std::cout << "\n1. Зарегистрировать транспортное средство" << std::endl;
            std::cout << "2. Начать гонку" << std::endl;
            std::cout << "3. Отмена (вернуться в главное меню)" << std::endl;
            std::cout << "Выберите действие: ";

            std::cin >> choice;

            switch (choice) {
            case 1: {
                std::cout << "\nДоступные транспортные средства:" << std::endl;
                int index = 1;
                std::vector<std::string> availableVehicles;

                for (const auto& [name, vehicle] : vehicleMap) {
                    bool canRegister = true;

                    if (canRegister) {
                        std::cout << index << ". " << name << std::endl;
                        availableVehicles.push_back(name);
                        index++;
                    }
                }

                std::cout << "0. Назад" << std::endl;
                std::cout << "Выберите транспортное средство: ";

                int vehicleChoice;
                std::cin >> vehicleChoice;

                if (vehicleChoice > 0 && vehicleChoice <= availableVehicles.size()) {
                    std::string selectedVehicle = availableVehicles[vehicleChoice - 1];
                    if (race.registerVehicle(vehicleMap[selectedVehicle])) {
                        std::cout << "Транспортное средство '" << selectedVehicle << "' зарегистрировано!" << std::endl;
                    }
                    else {
                        std::cout << "Это транспортное средство уже зарегистрировано!" << std::endl;
                    }
                }
                break;
            }

            case 2: {
                if (race.getVehicleCount() < 2) {
                    std::cout << "Для начала гонки нужно зарегистрировать хотя бы 2 транспортных средства!" << std::endl;
                    break;
                }

                auto results = race.startRace();

                std::cout << "\n=== РЕЗУЛЬТАТЫ ГОНКИ ===" << std::endl;
                std::cout << "Тип: " << Race::raceTypeToString(race.getType()) << std::endl;
                std::cout << "Дистанция: " << race.getDistance() << " км" << std::endl;
                std::cout << "\nМесто | Транспортное средство | Время" << std::endl;
                std::cout << "----------------------------------------" << std::endl;

                for (size_t i = 0; i < results.size(); i++) {
                    std::cout << i + 1 << " | " << results[i].first << " | " << results[i].second << " ч" << std::endl;
                }

                inRaceMenu = false;
                break;
            }

            case 3:
                inRaceMenu = false;
                break;

            default:
                std::cout << "Неверный выбор!" << std::endl;
            }
        }
    }

    FreeLibrary(dllHandle);
    std::cout << "До свидания!" << std::endl;
    return 0;
}