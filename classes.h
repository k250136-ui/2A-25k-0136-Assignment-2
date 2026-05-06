#include<iostream>
#include<string>

using namespace std;

class Engine
{
private:
    int engineId;
    string engineType;
    double displacement;
    int horsepower;
    double torque;
    int cylinders;

public:
    Engine() : engineId(0), engineType("Unknown"), displacement(0),
               horsepower(0), torque(0), cylinders(0) {}

    Engine(int id, string type, double disp, int hp, double tq, int cyl)
        : engineId(id), engineType(type), displacement(disp),
          horsepower(hp), torque(tq), cylinders(cyl) {}

    Engine(const Engine &e)
        : engineId(e.engineId), engineType(e.engineType),
          displacement(e.displacement), horsepower(e.horsepower),
          torque(e.torque), cylinders(e.cylinders) {}

    int getEngineId() const { return engineId; }
    string getEngineType() const { return engineType; }
    int getHorsepower() const { return horsepower; }
    int getCylinders() const { return cylinders; }

    void updateEngineType(const string &t) { engineType = t; }
    void updateDisplacement(double d) { displacement = d; }
    void updateHorsepower(int hp) { horsepower = hp; }
    void updateTorque(double t) { torque = t; }
    void updateCylinders(int c) { cylinders = c; }

    string getSpecs() const
    {
        return engineType + " | " + to_string((int)displacement) + "cc | " +
               to_string(horsepower) + "hp | " + to_string((int)torque) + "Nm | " +
               to_string(cylinders) + " cyl";
    }

    bool isHighPerformance() const { return horsepower > 200; }

    double calculateEfficiency() const
    {
        if (displacement <= 0)
            return 0;
        return (double)15000 / displacement;
    }

    void display() const
    {
        cout << "  [Engine #" << engineId << "] " << getSpecs()
             << " | Est. " << calculateEfficiency() << " km/L\n";
    }
};