#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
// the main class the root:
class Car
{
    private:
    string fullnName;
    string racingTeam;
    string type;
    int carNumber;
    int speed;
    int age;
    int capacity;

    public:
    Car(string const &fn,string const &rt ,string const &t,int s ,int cn,int a,int c )
    {
        setFullName(fn);
        serRacingTeam(rt);
        setType(t);
        setCapacity(c);
        setCarNumber(cn);
        setSpeed(s);
        setAge(a);
    }

    // getters :
    int getCarNumber ()const {return carNumber;}
    int getSpeed()const{return speed;}
    int getAge()const{return age;}
    int getCapacity()const{return capacity;}
    string getType(){return type;}
    string getFullName(){return fullnName;}
    string getRacingTeam(){return racingTeam;}
    // setters
    void setCarNumber(int c)
    {
        if(c>0)
        carNumber = c;
    }
    void setSpeed(int s)
    {
        if(s>0)
        {
            speed = s;
        }
    }
    void setAge(int a)
    {
        if(a>=0) // maybe zero if it just started the first race
            age = a;
    }
    void setCapacity(int c)
    {
        if(c>0)
        {
            capacity = c;
        }
    }
    void setType(string const &t)
    {
        type = t;
    }
    void setFullName(string const &f)
    {
        fullnName = f;
    }
    void serRacingTeam(string const &rt)
    {
        racingTeam = rt;
    }
// the main methods that will be override

    virtual int calculatePerformanceScore ()
    {
return 0;
    }

    virtual string toCSV() const {

        return type + "," +
            fullnName +","+ racingTeam + "," +
               to_string(speed) + "," + to_string(carNumber) + "," +
               to_string(age) + "," + to_string(capacity);
    }
 virtual void display()
    {
        cout<<"Car Number: "<<carNumber<<endl;
        cout<<"Type: "<<type<<endl;
        cout<<"Full Name: "<<fullnName<<endl;
        cout<<"Racing Team: "<<racingTeam<<endl;
        cout<<"Capacity: "<<capacity<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"speed: "<<speed<<endl;
    }


};
// the Racer
class Racer : public  Car
{
private:
    int nomOfRaceseCompleted ;
    int lapsComppleted;
public:
    Racer (string const &fn, string const &rt, int const s, int  const cn, int const a, int const c, int const norc, int const laps)
        :Car(fn,rt,"Racer",s,cn,a,c)
    {
        setNomOfRacesesCompleted(norc);
       setLapsCompleted(laps);
    }

    int getNomOfRacesesCompleted()const{return nomOfRaceseCompleted;}
    int getLapsCompleted ()const
    {
        return lapsComppleted;
    }

    //setters

    void setNomOfRacesesCompleted(int norc)
    {
        if(norc>=0)
        {
            nomOfRaceseCompleted=norc;
        }
    }

    void setLapsCompleted(int laps)
    {
        if(laps>=0)
        {
            lapsComppleted = laps;
        }
    }

    int calculatePerformanceScore()  override
    {
        return getSpeed()*10+getCapacity() ;
    }

    string toCSV() const override
    {
        return Car::toCSV() + "," + to_string(nomOfRaceseCompleted ) + "," + to_string(lapsComppleted);
    }

    void display() override
    {
        Car::display();
        cout << "Races Completed: " << nomOfRaceseCompleted << endl;
        cout << "Laps Completed: " << lapsComppleted << endl;
    }
};
// the supported car
class SupportedVeichles : public Car
 {
 private:
     int crewSize;
     double reliabilityRatig;

 public:
     SupportedVeichles(string const &fn, string const &rt, int const s, int  const cn, int const a, int const c, int const cs, double const rr):
     Car(fn,rt,"Supported Veichle",s,cn,a,c)
     {
         setCrewSize(cs);
         setReliabilityRatig(rr);
     }
     // getters
     int getCrewSize()const{return crewSize;}
     double getReliabilityRatig()const{return reliabilityRatig;}

     //seters
     void setCrewSize(int c)
     {
         if(c>0)
         {
             crewSize = c;
         }
     }
     void setReliabilityRatig(double r)
     {
         if(r>0)
         {
             reliabilityRatig=r;
         }
     }
     //-------------------------- overrided method
     int calculatePerformanceScore() override
     {
         return getSpeed()*5+getCapacity()*5;
     }
     string toCSV() const override
     {
         return Car::toCSV() + "," + to_string(crewSize) + "," + to_string(reliabilityRatig);
     }
    void display() override
     {
         Car::display();
         cout << "Crew Size: " << crewSize << endl;
         cout << "Reliability Rating: " << reliabilityRatig << endl;
     }
 };
// the garage manager class
class GarageManager
{
    string fileName = "garage_db.txt";
    vector<Car *> vehicles;

 public:

    //
 void save_to_DB(const string& fileName = "garage_db.txt") {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Could not open file for writing\n";
            return;
        }

        for (const auto& car : vehicles) {
            file << car->toCSV() << "\n";
        }

        file.close();
    }

    // initialize method
    void readDB (string fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            return;
        }
        string line;
        while (getline(file,line))
        {
            stringstream subtr(line);
            // declare the base variables
            string type, fullName, racingTeam; // the string
            string carNumber, speed, age, capacity; // will be int
            getline(subtr,type,',');
            getline(subtr,fullName,',');
            getline(subtr,racingTeam,',');
            getline(subtr,speed,',');
            getline(subtr,carNumber,',');
            getline(subtr,age,',');
            getline(subtr,capacity,',');

            if (type=="Racer")
            {
                string nomOfRaceseCompleted, lapsCompleted;
                getline(subtr,nomOfRaceseCompleted,',');
                getline(subtr,lapsCompleted,',');
                vehicles.push_back(new Racer(fullName,
                    racingTeam,
                    stoi(speed),
                    stoi(carNumber),
                    stoi(age),
                    stoi(capacity),
                    stoi(nomOfRaceseCompleted),
                    stoi(lapsCompleted))); // add racer car
            }
            else if (type=="Supported Veichle")
            {
                string crewSize; // int
                string reliabilityRatig; // double
                getline(subtr,crewSize,',');
                getline(subtr,reliabilityRatig,',');
                vehicles.push_back(new SupportedVeichles(
                fullName,
                racingTeam,
                stoi(speed),
                stoi(carNumber),
                stoi(age),
                stoi(capacity),
                stoi(crewSize),
                stod(reliabilityRatig)
            )); // add supported vehicle
            }
        }
    }

// add car with check that the car isn't exist
    void addCar(Car *c)
    {
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i]->getCarNumber() == c->getCarNumber())
            {
                cout << "Car " << c->getFullName() << " already exists." << endl;
                return;
            }
        }
        vehicles.push_back(c);
        cout << "Car " << c->getFullName() << " added." << endl;
        save_to_DB(fileName);
    }
    // view the cars in the garage
   void viewCars()
 {
     for (int i = 0; i < vehicles.size(); i++)
     {
         cout<<i+1<<" "; vehicles[i]->display();
         cout<<"-------------------------------"<<"\n";
     }
 }
//---------------------------------------------------------//
    //----------------- tune_up------------------//
    void tune_up ()
 {
     viewCars();
     cout << "Enter the number of the car you want to update: ";
     int carNumber;
     cin >> carNumber;

     Car* car = findCar(carNumber);
     if (car != NULL)
     {
         cout << "1. Update Speed\n";
         cout << "2. Update Capacity\n";
         cout << "3. Update Age\n";
         cout << "4. Update Racing Team\n";
         cout << "Enter your choice: ";
         int choice;
         cin >> choice;

         if (choice == 1)
         {
             int s;
             cout << "Enter new speed: ";
             cin >> s;
             car->setSpeed(s);
         }
         else if (choice == 2)
         {
             int c;
             cout << "Enter new capacity: ";
             cin >> c;
             car->setCapacity(c);
         }
         else if (choice == 3)
         {
             int a;
             cout << "Enter new age: ";
             cin >> a;
             car->setAge(a);
         }
         else if (choice == 4)
         {
             string team;
             cout << "Enter new team: ";
             cin.ignore();
             getline(cin, team);
             car->serRacingTeam(team);
         }
         else
         {
             cout << "Invalid choice\n";
             return;
         }

         cout << "Car updated successfully\n";
         save_to_DB(fileName);
     }
 }
// -------------------------------------------------------------------------//
    //------------------- find by number ------------------------//

    Car* findCar(int number) const
 {
     for (Car* car : vehicles)
     {
         if (car->getCarNumber() == number)
         {
             cout << "\n (founded) Vehicle Details:" << endl;
             car->display();
             return car;
         }
     }

     cout << "No vehicle found with number: " << number << endl;
     return nullptr;
 }
    //-------------------------------- find by name -------------------------//

     void findCar(const string& name) const
     {
      bool found = false;
         for (Car* car : vehicles)
         {
             if (car->getFullName() == name)
             {
                 cout << "(founded) Vehicle Details:" << endl;
                 car->display();
             found = true;
             }
         }
     if (!found)
         cout << "No vehicle found with name: " << name << endl;
     }
    // ---------------------------------------------------------------------//
    //-------------------- retire ----------------------------------------//
    void rtire ()
 {
     viewCars();
     cout<<"select the car you want to rtire\n";
     int carNumber;
     cin>>carNumber;
     Car* car = findCar(carNumber);
     if (car != nullptr)
     {
          for (int i = 0; i < vehicles.size(); i++)
          {
              if (vehicles[i]->getCarNumber() == car->getCarNumber())
              {
                  vehicles.erase(vehicles.begin()+i); // delete it
                  break;
              }
          }
         save_to_DB(fileName);
     }
 }

    void garageReport()
 {

     if (vehicles.empty())
     {
         cout << "Garage is empty!" << endl;
         return;
     }

     int totalCars = vehicles.size();
     double totalScore = 0;
     for (int i = 0; i < vehicles.size(); i++)
     {
         totalScore += vehicles[i]->calculatePerformanceScore();
     }

     vector<pair<string, int>> teamCounts;

     for (int i = 0; i < vehicles.size(); i++)
     {
         string currentTeam = vehicles[i]->getRacingTeam();
         bool found = false;
         for (int j = 0; j < teamCounts.size(); j++)
         {
             if (teamCounts[j].first == currentTeam)
             {
                 teamCounts[j].second++;
                 found = true;
                 break;
             }
         }
         if (!found)
         {
             teamCounts.push_back({currentTeam, 1});
         }
     }

     cout << "============= Garage Report =============" << endl;
     cout << "-----------------------------------------"<<endl;
     cout<<"Total number of cars: "<<totalCars<<endl;
     cout << "avr score: " << totalScore/totalCars << endl;
     cout << "\n--- Breakdown by Racing Team ---" << endl;
     for (int i = 0; i < teamCounts.size(); i++)
     {
         cout << "team: " << teamCounts[i].first << " : " << teamCounts[i].second << " cars" << endl;
     }
 }

};



int main()
{
    GarageManager manager;

    // read from db first
    manager.readDB("garage_db.txt");

    int choise = 0;

    while (choise != 8)
    {
        if (cin.fail())
        {

        }
        cout << "\n=== welcome to garage system ===\n";
        cout << "1. add new car\n";
        cout << "2. veiw all cars\n";
        cout << "3. tune up (updat)\n";
        cout << "4. find car by num\n";
        cout << "5. find car by name\n";
        cout << "6. retire a car\n";
        cout << "7. garag report\n";
        cout << "8. exit\n";
        cout << "entere your choise: ";
        cin >> choise;

        if (choise == 1)
        {
            cout << "\nwhat type?\n1. Racer\n2. support veichle\nchoise: ";
            int typ;
            cin >> typ;

            string fn, rt;
            int s, cn, a, c;

            cout << "enter full name: ";
            cin.ignore();
            getline(cin, fn);

            cout << "enter racing team: ";
            getline(cin, rt);

            cout << "enter speed: "; cin >> s;
            cout << "enter car number: "; cin >> cn;
            cout << "enter age: "; cin >> a;
            cout << "enter capaciy: "; cin >> c;

            if (typ == 1)
            {
                int races, laps;
                cout << "enter races compleeted: "; cin >> races;
                cout << "enter laps: "; cin >> laps;

                manager.addCar(new Racer(fn, rt, s, cn, a, c, races, laps));
            }
            else if (typ == 2)
            {
                int crew; double rel;
                cout << "enter crew size: "; cin >> crew;
                cout << "enter reliablaty: "; cin >> rel;

                manager.addCar(new SupportedVeichles(fn, rt, s, cn, a, c, crew, rel));
            }
            else
            {
                cout << "invaild type!\n";
            }
        }
        else if (choise == 2)
        {
            cout << "\n--- all cars ---\n";
            manager.viewCars();
        }
        else if (choise == 3)
        {
            manager.tune_up();
        }
        else if (choise == 4)
        {
            int num;
            cout << "enter car number: ";
            cin >> num;
            manager.findCar(num);
        }
        else if (choise == 5)
        {
            string n;
            cout << "enter car name: ";
            cin.ignore();
            getline(cin, n);
            manager.findCar(n);
        }
        else if (choise == 6)
        {
            manager.rtire();
        }
        else if (choise == 7)
        {
            manager.garageReport();
        }
        else if (choise == 8)
        {
            cout << "good bye!\n";
        }
        else
        {
            cout << "wrong choise try again\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

    }

    return 0;
}