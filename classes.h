#include<iostream>
#include<string>
#include<fstream>

using namespace std;

const int MAX_LISTINGS = 100;
const int MAX_BUYERS = 30;
const int MAX_SELLERS = 30;
const int MAX_ADMINS = 5;
const int MAX_MESSAGES = 200;
const int MAX_FAVORITES = 20;

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
	Engine() : engineId(0), engineType("Unknown"), displacement(0), horsepower(0), torque(0), cylinders(0) {}

	Engine(int id, const string &type, double disp, int hp, double tq, int cyl)
		: engineId(id), engineType(type), displacement(disp), horsepower(hp), torque(tq), cylinders(cyl) {}

        // No custom copy constructor is needed because Engine only stores simple value members.

	int getEngineId() const { return engineId; }
	string getEngineType() const { return engineType; }
	double getDisplacement() const { return displacement; }
	int getHorsepower() const { return horsepower; }
	double getTorque() const { return torque; }
	int getCylinders() const { return cylinders; }

	void display() const
	{
		cout << "Engine: " << engineType << " " << displacement << "cc | "
			 << horsepower << "hp | " << torque << "Nm | " << cylinders << " cyl\n";
	}
};

class Address
{
private:
	string street, city, province;

public:
	Address() : street(""), city(""), province("") {}
	Address(const string &st, const string &ct, const string &pv) : street(st), city(ct), province(pv) {}

	void display() const
	{
		cout << street << ", " << city << ", " << province;
	}
};

