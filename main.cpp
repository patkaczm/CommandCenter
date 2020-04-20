#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <chrono>

class Vehicle {
public:
    enum class type {
        Police,
        Ambulance,
        FireBrigade,
        WaterRescue
    };

    virtual std::string getName() = 0;
    virtual type getType() = 0;
    virtual std::chrono::minutes restTime() = 0;
    virtual std::size_t getSize() = 0;
};

class Police: public Vehicle {
public:
    explicit Police(std::size_t s) : size(s) {}
    std::string getName() override {return "Police"; }
    type getType() override {return type::Police;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
private:
    std::size_t size;
};

class Ambulance: public Vehicle {
public:
    explicit Ambulance(std::size_t s) : size(s) {}
    std::string getName() override {return "Ambulance"; }
    type getType() override {return type::Ambulance;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
private:
    std::size_t size;
};

class FireBrigade: public Vehicle {
public:
    explicit FireBrigade(std::size_t s) : size(s) {}
    std::string getName() override {return "Fire Brigade"; }
    type getType() override {return type::FireBrigade;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
private:
    std::size_t size;
};

class WaterRescue: public Vehicle {
public:
    explicit WaterRescue(std::size_t s) : size(s) {}
    std::string getName() override {return "Police"; }
    type getType() override {return type::WaterRescue;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
private:
    std::size_t size;
};

class Accident {
public:
private:
    std::vector<Vehicle> delegatedUnits;
    std::time_t t;
};

int main() {
    bool run {true};
    char wybor;
    while(run) {
        std::cout << "1. Dodaj zdarzenie\n"
                  << "2. Historia zdarzen\n"
                  << "3. Wylacz program.";
        std::cin >> wybor;
        switch(wybor) {
            case '3':
                run = false;
                break;
        }
    }
}
