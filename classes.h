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

class Engine {
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

class Address   {
private:
	string street, city, province;

public:
	Address() : street(""), city(""), province("") {}
	Address(string street, string city, string province) : street(street), city(city), province(province) {}

	void display() const
	{
		cout << street << ", " << city << ", " << province;
	}
};

class Vehicle {
protected:
	int vehicleID;
	string brand, model,color;
	int year,mileage;
	static int totalvehicles;

public:
	Vehicle() : vehicleID(0), brand("Unknown"), model("unknown"), color("unknown"), year(2000), mileage(0) 
	{
		totalvehicles++;
	}

	Vehicle(int vehicleID, string brand, string model, string color, int year,int mileage) :
		vehicleID(vehicleID), brand(brand), model(model), color(color), year(year), mileage(mileage) 
		{
			totalvehicles++;
		}

	virtual ~Vehicle()
	{
		totalvehicles--;
	}

	// exception handling
	void setyear(int yr)
	{
		if (yr < 1980 || yr > 2026)
		{
			throw string("invalid! enter year between 1980 and 2026");
		}
		year = yr;
	}

	void setmileage(int mil)
	{
		if (mil < 0 || mil > 1000000)
		{
			throw string("invalid! enter mileage between 0 and 1000000");
		}
		mileage = mil;
	}

	int getvehicleID() { return vehicleID; }
	string getbrand() { return brand; }
	string getmodel() { return model; }
	string getcolor() { return color; }
	int getyear() { return year; }
	int getmileage() { return mileage; }
	static int getTotalvehicles() { return totalvehicles; }

	bool operator==(const Vehicle &other) const 
	{
		return vehicleID == other.vehicleID;
	}

	virtual void displaySpecs() const = 0;
	virtual string getType() const = 0;
	virtual Vehicle *copy() const = 0;
	virtual void writeTypeData(ofstream &fout) const = 0;
};

int Vehicle::totalvehicles = 0;

class Car : public Vehicle {
private:
	Engine engine;
	string bodyType;

public:
	Car() : Vehicle(), engine(), bodyType("Saden") {}
	Car(int vehicleID, string brand, string model, string color, int year,int mileage, Engine engine, string bodyType) :
		Vehicle(vehicleID,brand,model,color,year,mileage), engine(engine), bodyType(bodyType) {}

	~Car() {}
	
	string getType() const { return bodyType; }

	void displaySpecs() const
	{
		cout << "Vehicle Type: Car" << endl;
		cout << "Vehicle ID: " << vehicleID << "||"
			 << "Brand: " << brand << "||"
			 << "Model: " << model << "||"
			 << "color: " << color << "||"
			 << "Mileage : " << mileage << "||"
			 << "year: " << brand << "||" << endl;
			 engine.display();
	}

	Vehicle *copy() const
	{
		return new Car(*this);
	}
	
	void writeTypeData(ofstream &fout) const
	{
		fout << bodyType << "||"
		<< engine.getEngineId() << "||"
		<< engine.getEngineType() << "||"
		<< engine.getDisplacement() << "||"
		<< engine.getHorsepower() << "||"
		<< engine.getTorque() << "||"
		<< engine.getCylinders();
	}
	
};

class Bike : public Vehicle {
private:
	int engineCC;
	bool hasCarrier;

public:
	Bike() : Vehicle(), engineCC(70), hasCarrier(true) {}
	
	Bike(int vehicleID, string brand, string model, string color, int year,int mileage, int engineCC, bool hasCarrier) :
		Vehicle(vehicleID,brand,model,color,year,mileage), engineCC(engineCC), hasCarrier(hasCarrier) {}

	~Bike() {}

	string getType() const { return "Bike"; }

	void displaySpecs() const
	{
		cout << "Vehicle Type: Byke" << endl;
		cout << "Vehicle ID: " << vehicleID << "||"
			 << "Brand: " << brand << "||"
			 << "Model: " << model << "||"
			 << "color: " << color << "||"
			 << "Mileage : " << mileage << "||"
			 << "year: " << brand << "||" << endl
			 << "Engine CC: " << engineCC << "||" << endl
			 << "Carrier: " << (hasCarrier ? "Yes" : "NO") << "||" << endl;
	}

	Vehicle *copy() const
	{
		return new Bike(*this);
	}

	void writeTypeData(ofstream &fout) const
	{
		fout << engineCC << "|| " << (hasCarrier ? 1 : 0);  
	}

};

