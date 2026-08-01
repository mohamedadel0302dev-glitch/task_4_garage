#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
     //--------------------------
     int calculatePerformanceScore() override
     {
         return getSpeed()*5+getCapacity()*5;
     }
 };
// the garage manager class
class GarageManager
{
  vector<Car *> vehicles;

 public:
    // initalize method
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
            getline(subtr,carNumber,',');
            getline(subtr,speed,',');
            getline(subtr,age,',');
            getline(subtr,capacity,',');

            if (type=="Racer")
            {
                string nomOfRaceseCompleted, lapsCompleted;
                getline(subtr,nomOfRaceseCompleted,',');
                getline(subtr,lapsCompleted,',');
                vehicles.push_back(new Racer(fullName,
                    racingTeam,stoi(speed),
                    stoi(carNumber),stoi(age),
                    stoi(capacity),stoi(nomOfRaceseCompleted),
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
    }

};



int main()
{



    return 0;
     // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}