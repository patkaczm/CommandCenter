#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <chrono>
#include <memory>

class Vehicle {
public:
    enum class type {
        Police,
        Ambulance,
        FireBrigade,
        WaterRescue
    };

    explicit Vehicle(std::size_t s) : size(s), busy(false) {static int _id{}; id = _id++;}
    virtual std::string getName() = 0;
    virtual type getType() = 0;
    virtual std::chrono::minutes restTime() = 0;

    std::size_t getSize() {return size;}

    void dispose() {busy = true;}
    void rest() {busy = false;}
    bool isBusy() {return busy;}

    int getId() {return id;}
protected:
    std::size_t size;
    bool busy;
private:
    int id;
};

class Police: public Vehicle {
public:
    explicit Police(std::size_t s) : Vehicle(s) {}
    std::string getName() override {return "Police"; }
    type getType() override {return type::Police;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
};

class Ambulance: public Vehicle {
public:
    explicit Ambulance(std::size_t s) : Vehicle(s) {}
    std::string getName() override {return "Ambulance"; }
    type getType() override {return type::Ambulance;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
};

class FireBrigade: public Vehicle {
public:
    explicit FireBrigade(std::size_t s) : Vehicle(s) {}
    std::string getName() override {return "Fire Brigade"; }
    type getType() override {return type::FireBrigade;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
};

class WaterRescue: public Vehicle {
public:
    explicit WaterRescue(std::size_t s) : Vehicle(s) {}
    std::string getName() override {return "Water rescue"; }
    type getType() override {return type::WaterRescue;}
    std::chrono::minutes restTime() override { return std::chrono::minutes(15);}
};

class Accident {
public:
    enum class type {
        CarCrash,
        Fire,
        Drown,
        HeartStroke
    };
    void addVehicle(std::shared_ptr<Vehicle> v) { delegatedUnits.emplace_back(v);}
    virtual bool isVehicleNeededInAccident(std::shared_ptr<Vehicle> v) = 0;
    virtual std::string getType() = 0;

private:
    std::vector<std::shared_ptr<Vehicle>> delegatedUnits;
    std::chrono::steady_clock::time_point out;
    std::chrono::minutes duration;
};

class CarCrashAccident: public Accident {
public:
    std::string getType() override {return "Car crash";}
    bool isVehicleNeededInAccident(std::shared_ptr<Vehicle> v) override {
        return v->getType() == Vehicle::type::Ambulance || v->getType() == Vehicle::type::Police || v->getType() == Vehicle::type::FireBrigade;
    }
};

class FireAccident: public Accident {
public:
    std::string getType() override {return "Fire";}
    bool isVehicleNeededInAccident(std::shared_ptr<Vehicle> v) override {
        return v->getType() == Vehicle::type::FireBrigade;
    }
};

class DrownAccident: public Accident {
public:
    std::string getType() override {return "Drown";}
    bool isVehicleNeededInAccident(std::shared_ptr<Vehicle> v) override {
        return v->getType() == Vehicle::type::Ambulance || v->getType() == Vehicle::type::Police || v->getType() == Vehicle::type::WaterRescue;
    }
};

class HeartStrokeAccident: public Accident {
public:
    std::string getType() override {return "Heart stroke";}
    bool isVehicleNeededInAccident(std::shared_ptr<Vehicle> v) override {
        return v->getType() == Vehicle::type::Ambulance;
    }
};

class CommandCenter {
public:
    CommandCenter() {
        units.emplace_back(std::move(std::make_shared<Police>(1)));
        units.emplace_back(std::move(std::make_shared<Police>(1)));
        units.emplace_back(std::move(std::make_shared<Police>(2)));
        units.emplace_back(std::move(std::make_shared<Police>(2)));
        units.emplace_back(std::move(std::make_shared<FireBrigade>(1)));
        units.emplace_back(std::move(std::make_shared<FireBrigade>(1)));
        units.emplace_back(std::move(std::make_shared<FireBrigade>(2)));
        units.emplace_back(std::move(std::make_shared<FireBrigade>(2)));
        units.emplace_back(std::move(std::make_shared<Ambulance>(1)));
        units.emplace_back(std::move(std::make_shared<Ambulance>(1)));
        units.emplace_back(std::move(std::make_shared<Ambulance>(2)));
        units.emplace_back(std::move(std::make_shared<Ambulance>(2)));
        units.emplace_back(std::move(std::make_shared<WaterRescue>(1)));
        units.emplace_back(std::move(std::make_shared<WaterRescue>(1)));
        units.emplace_back(std::move(std::make_shared<WaterRescue>(2)));
        units.emplace_back(std::move(std::make_shared<WaterRescue>(2)));
    }

    std::vector<std::shared_ptr<Vehicle>> getAvailableUnits() {
        std::vector<std::shared_ptr<Vehicle>> au;
        for(const auto& unit : units) {
            if (!unit->isBusy()) {
                au.emplace_back(unit);
            }
        }
        return au;
    }

private:
    std::vector<std::shared_ptr<Vehicle>> units;
};

int main() {
    bool run {true};
    char wybor;

    CommandCenter cc;

    while(run) {
        std::cout << "1. Dodaj zdarzenie\n"
                  << "2. Historia zdarzen\n"
                  << "3. Wylacz program.";
        std::cin >> wybor;
        switch(wybor) {
            case '1': {
                bool run1 = true;
                std::shared_ptr<Accident> acc;
                while(run1) {
                    std::cout << "Typ zdarzenia: \n1. Car crash.\n2. Fire.\n3. Drown.\n4. Stroke.\n5. Quit.\n";
                    char act;
                    std::cin >> act;
                    switch (act) {
                        case '1':
                            acc = std::make_shared<CarCrashAccident>();
                            run1 = false;
                            break;
                        case '2':
                            acc = std::make_shared<FireAccident>();
                            run1 = false;
                            break;
                        case '3':
                            acc = std::make_shared<DrownAccident>();
                            run1 = false;
                            break;
                        case '4':
                            acc = std::make_shared<HeartStrokeAccident>();
                            run1 = false;
                            break;
                        case '5':
                            run1 = false;
                            break;
                    }
                }
                run1 = true;
                while(run1) {
                    std::cout << "-1: wyjscie";
                    std::cout << "Dodaj jednostki: ";
                    auto au = cc.getAvailableUnits();
                    for (int i = 0; i < au.size(); i++) {
                        std::cout << au[i]->getId() << ". jednostka: " << au[i]->getName() << " rozmiar: " << au[i]->getSize()
                                  << "\n";
                    }
                    int act;
                    std::cin >> act;
                    if (act == -1) {
                        run1=false;
                        continue;
                    }
                    auto found = std::find_if(begin(au), end(au), [act](std::shared_ptr<Vehicle> a){ return a->getId() == act;});
                    if (found != au.end() && acc->isVehicleNeededInAccident(*found)) {
                        std::cout << "Unit disposed.\n";
                        (*found)->dispose();
                    } else {
                        std::cout << "This unit is not needed for this accident.\n";
                    }
                }

            }
                break;
            case '2':
                break;
            case '3':
                run = false;
                break;
        }
    }
}
