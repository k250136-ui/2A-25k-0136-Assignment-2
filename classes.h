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

	int getvehicleID() const { return vehicleID; }
	string getbrand() const { return brand; }
	string getmodel() const { return model; }
	string getcolor() const { return color; }
	int getyear() const { return year; }
	int getmileage() const { return mileage; }
	
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

ostream &operator<<(ostream &out, const Vehicle &v)
{
	out << v.getType() << " [ID: " << v.getvehicleID() << "] "
		<< v.getbrand() << " " << v.getmodel() << " " << v.getyear();
	return out;
}

class Listing {
private:
	int listingId;
	int sellerId;
	double price;
	string description;
	string status;
	string postedDate;
	Vehicle *vehicle; 
	static int totalListings;

public:
	Listing() : listingId(0), sellerId(0), price(0), description(""), status("pending"), postedDate(""), vehicle(0)
	{
		totalListings++;
	}

	Listing(int id, int sid, double p, const string &desc, const string &date, Vehicle *v)
		: listingId(id), sellerId(sid), description(desc), status("pending"), postedDate(date), vehicle(v)
	{
		setPrice(p);
		totalListings++;
	}

	Listing(const Listing &other) : listingId(other.listingId) , sellerId(other.sellerId), price(other.price), 
	description(other.description), status(other.status), postedDate(other.postedDate) 
	{
		vehicle = ( other.vehicle != 0 ) ? other.vehicle->copy() : 0;
		totalListings++;
	}

	Listing &operator=(const Listing &other)
	{
		if (this != &other)
		{
			delete vehicle;
			listingId = other.listingId;
			sellerId = other.sellerId;
			price = other.price;
			description = other.description;
			status = other.status;
			postedDate = other.postedDate;
			vehicle = (other.vehicle != 0) ? other.vehicle->copy() : 0;
		}
		return *this;
	}

	~Listing()
	{
		delete vehicle;
		vehicle = 0;
		totalListings--;
	}

	static int getTotalListings() { return totalListings; }

	int getListingId() const { return listingId; }
	int getSellerId() const { return sellerId; }
	double getPrice() const { return price; }
	string getStatus() const { return status; }
	string getDescription() const { return description; }
	string getPostedDate() const { return postedDate; }
	Vehicle *getVehicle() const { return vehicle; }

	void setPrice(double p)
	{
		if (p <= 0)
			throw string("Invalid price! Price must be greater than 0.");
		price = p;
	}

	void setStatus(const string &s) { status = s; }

	void update(double newPrice, const string &newDesc)
	{
		setPrice(newPrice);
		description = newDesc;
		status = "pending";
	}

	double operator*(double texPercent) const 
	{
		return price + (price * texPercent/100.0);
	}

	void display() const
	{
		cout << "\n Listing # " << listingId 
			 << " || Status: " 
			 << status << " || Seller#" 
			 << sellerId << endl;
		cout << "Price: PKR " << price << endl;
		cout << "Description: " << description << endl;
		cout << "Posted: " << postedDate << endl;
		if (vehicle != 0)
		{
			cout << "Short View: " << *vehicle << endl;
			vehicle->displaySpecs();
		}
	}

	void saveToFile(ofstream &fout) const
	{
		if (vehicle == 0)
			return;

		fout << listingId << "|"
			 << sellerId << "|"
			 << price << "|"
			 << description << "|"
			 << status << "|"
			 << postedDate << "|"
			 << vehicle->getType() << "|"
			 << vehicle->getvehicleID() << "|"
			 << vehicle->getbrand() << "|"
			 << vehicle->getmodel() << "|"
			 << vehicle->getyear() << "|"
			 << vehicle->getmileage() << "|"
			 << vehicle->getcolor() << "|";

		vehicle->writeTypeData(fout);
		fout << "\n";
	}

	friend void applyDiscount(Listing &l, double percent);
};

int Listing::totalListings = 0;

void applyDiscount(Listing &l, double percent)
{
	if (percent < 0 || percent > 90)
	{
		cout << "Invalid discount percentage!\n";
		return;
	}
	l.price = l.price - (l.price * percent / 100.0);
}

class User
{
protected:
	int userId;
	string name, email, phone, password;
	bool isActive;

	static int totalUsers;

public:
	User() : userId(0), name(""), email(""), phone(""), password(""), isActive(true) { totalUsers++; }
	User(int id, const string &n, const string &e, const string &ph, const string &pass)
		: userId(id), name(n), email(e), phone(ph), password(pass), isActive(true)
	{
		totalUsers++;
	}

	virtual ~User() { totalUsers--; }

	static int getTotalUsers() { return totalUsers; }

	int getUserId() const { return userId; }
	string getName() const { return name; }
	string getEmail() const { return email; }
	string getPhone() const { return phone; }
	bool getIsActive() const { return isActive; }

	void setActive(bool a) { isActive = a; }

	bool login(const string &e, const string &pass) const
	{
		return (email == e && password == pass);
	}

	// POLYMORPHISM: pure virtual functions
	virtual void displayProfile() const = 0;
	virtual string getRole() const = 0;

	// FRIEND FUNCTION #2
	friend void resetUserPassword(User &u, const string &newPass);
};

int User::totalUsers = 0;

void resetUserPassword(User &u, const string &newPass)
{
	u.password = newPass;
}

class SearchFilter
{
private:
	double minPrice, maxPrice;
	string brand;
	int minYear, maxYear;

public:
	SearchFilter() : minPrice(0), maxPrice(999999999), brand(""), minYear(1980), maxYear(2026) {}

	void setMinPrice(double p) { minPrice = p; }
	void setMaxPrice(double p) { maxPrice = p; }
	void setBrand(const string &b) { brand = b; }
	void setMinYear(int y) { minYear = y; }
	void setMaxYear(int y) { maxYear = y; }

	bool isMatch(const Listing &l) const
	{
		Vehicle *v = l.getVehicle();
		if (v == 0)
			return false;

		if (l.getStatus() != "active")
			return false;
		if (l.getPrice() < minPrice || l.getPrice() > maxPrice)
			return false;
		if (!brand.empty() && v->getbrand() != brand)
			return false;
		if (v->getyear() < minYear || v->getyear() > maxYear)
			return false;
		return true;
	}
};

class Buyer : public User
{
private:
	double budget;
	string preferredBrand, preferredCity;
	int favoriteIds[MAX_FAVORITES];
	int favCount;

public:
	Buyer() : User(), budget(0), preferredBrand(""), preferredCity(""), favCount(0) {}

	Buyer(int id, const string &n, const string &e, const string &ph, const string &pass,
		  double b, const string &pb, const string &pc)
		: User(id, n, e, ph, pass), budget(b), preferredBrand(pb), preferredCity(pc), favCount(0) {}

	~Buyer() {}

	string getRole() const { return "Buyer"; }

	void displayProfile() const
	{
		cout << "Buyer #" << userId << " | " << name << " | Budget: " << budget
			 << " | Favorites: " << favCount << "\n";
	}

	bool saveFavorite(int listingId)
	{
		if (favCount >= MAX_FAVORITES)
			return false;

		for (int i = 0; i < favCount; i++)
			if (favoriteIds[i] == listingId)
				return false;

		favoriteIds[favCount++] = listingId;
		return true;
	}

	void showFavorites() const
	{
		cout << "Favorites of " << name << ": ";
		if (favCount == 0)
		{
			cout << "None\n";
			return;
		}

		for (int i = 0; i < favCount; i++)
			cout << favoriteIds[i] << " ";
		cout << "\n";
	}
};

class Seller : public User
{
private:
	string companyName;
	double rating;
	int totalSales;
	bool isVerified;
	Address sellerAddress;

public:
	Seller() : User(), companyName(""), rating(0), totalSales(0), isVerified(false), sellerAddress() {}

	Seller(int id, const string &n, const string &e, const string &ph, const string &pass,
		   const string &comp, const Address &addr)
		: User(id, n, e, ph, pass), companyName(comp), rating(0), totalSales(0), isVerified(false), sellerAddress(addr) {}

	~Seller() {}

	string getRole() const { return "Seller"; }

	void displayProfile() const
	{
		cout << "Seller #" << userId << " | " << name << " | Company: " << companyName
			 << " | Rating: " << rating << "\n";
	}

	// EXCEPTION HANDLING: invalid rating check
	void setRating(double r)
	{
		if (r < 0 || r > 5)
			throw string("Invalid rating! Enter between 0 and 5.");
		rating = r;
	}

	// FRIEND FUNCTION #3
	friend double calculateSellerTrustScore(const Seller &s);
};

double calculateSellerTrustScore(const Seller &s)
{
	double verifiedBonus = s.isVerified ? 1.0 : 0.0;
	return (s.rating * 10.0) + (s.totalSales * 0.2) + verifiedBonus;
}