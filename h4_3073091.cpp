#include <iostream>
#include <iomanip>

using namespace std;

class Time
{
private:
    int minuteOfDay;
public:
    Time (unsigned int a = 0);
    Time (int stunde, int minute);
    ~Time();
    void set_time (int stunde, int minute);
    int get_hour ();
    int get_minute ();
    int get_minuteOfDay ();
    Time operator+(unsigned int a);
    friend istream& operator>>(istream&, Time&);
    friend ostream& operator<<(ostream&, Time&);
};

Time::~Time()
{}
Time::Time(unsigned int a)
{
    minuteOfDay = a % 1440;
}
void Time::set_time(int stunde, int minute)
{
    stunde = stunde % 24;
    stunde = stunde + (minute/60);
    minute = minute % 60;
    minuteOfDay = (stunde*60) + minute;
}
Time::Time(int stunde, int minute)
{
    set_time(stunde, minute);
}
int Time::get_hour()
{
    return (minuteOfDay/60);
}
int Time::get_minute()
{
    return (minuteOfDay%60);
}
int Time::get_minuteOfDay()
{
    return minuteOfDay;
}
istream& operator>>(istream& in, Time& t)
{
    int x, y;
    char c;
    in >> x >> c >> y;
    t.set_time(x,y);
    return in;
}
ostream& operator<<(ostream& out, Time& t)
{
    if (t.get_hour() < 10)
    {
        if (t.get_minute() < 10)
        {
            out << "0" << t.get_hour() << ":" << "0" << t.get_minute();
        }
        else
        {
            out << "0" << t.get_hour() << ":" << t.get_minute();
        }
    }
    else
    {
        if (t.get_minute() < 10)
        {
            out << t.get_hour() << ":" << "0" << t.get_minute();
        }
        else
        {
            out << t.get_hour() << ":" << t.get_minute();
        }
    }
    return out;
}
Time Time::operator+(unsigned int a)
{
    return Time(get_hour(), (get_minute() + a));
}

class Train
{
private:
    string no, to, over;
public:
    Train(string a, string b, string c);
    ~Train();
    string get_no();
    string get_to();
    string get_over();
};
Train::Train(string a, string b, string c):
    no(a),
    to(b),
    over(c)
    {}
Train::~Train()
{
    cout << "Train " << no << " to " << to << " deleted ";
}
string Train::get_no()
{
    return no;
}
string Train::get_to()
{
    return to;
}
string Train::get_over()
{
    return over;
}

class Station
{
private:
    const string station;
    static const unsigned int numberOfPlatforms = 15;
    Train *schedule[1440][numberOfPlatforms];
public:
    Station(string d):
        station(d)
        {
            for (unsigned int z1 = 0; z1 < 1440; z1++)
            {
                for (unsigned int z2 = 0; z2 < numberOfPlatforms; z2++)
                {
                    schedule[z1][z2] = nullptr;
                }
            }
        }
    ~Station();
    void addDeparture(Time timeIn, unsigned int platformNo, Train *t2)
    {
        if ((platformNo > numberOfPlatforms)||(platformNo <= 0))
        {
            cout << "Wrong platform. No change is saved!" << endl;
        }
        else
        {
            schedule[timeIn.get_minuteOfDay()][platformNo-1] = t2;
        }
    }
    void showDeparture(Time t3, unsigned int wieVielMin)
    {
        Time t8;
        t8 = t3 + wieVielMin;
        cout << endl << station << endl << "DEPARTURES ";
        cout << t3;
        cout << "-";
        cout << t8 << endl;
        cout << "========================" << endl << "Time" << setw(10) << "Train" << setw(7) << "over" << setw(53)
        << "to" << setw(25) << "platform" << endl;
        if ((t3.get_minuteOfDay()+wieVielMin) < 1440){
        for (unsigned int z5 = t3.get_minuteOfDay(); z5 < (t3.get_minuteOfDay()+wieVielMin); z5++)
        {
            for (unsigned int z6 = 0; z6 < numberOfPlatforms; z6++)
            {
                if (schedule[z5][z6] != nullptr)
                {
                    Time t7;
                    t7 = t7 + z5;
                    int z7;
                    z7 = 1 + (z6+1)/10;
                    cout << t7 << setw(4+schedule[z5][z6]->get_no().size()) << schedule[z5][z6]->get_no()
                    << setw(8-schedule[z5][z6]->get_no().size()+schedule[z5][z6]->get_over().size())
                    << schedule[z5][z6]->get_over()
                    << setw(55-schedule[z5][z6]->get_over().size()+schedule[z5][z6]->get_to().size())
                    << schedule[z5][z6]->get_to()
                    << setw(19-schedule[z5][z6]->get_to().size()+z7) << z6+1 << endl;
                    t7.~Time();
                }
            }
        }
        }
        else
        {
            for (unsigned int z5 = t3.get_minuteOfDay(); z5 < 1440; z5++)
        {
            for (unsigned int z6 = 0; z6 < numberOfPlatforms; z6++)
            {
                if (schedule[z5][z6] != nullptr)
                {
                    Time t7;
                    t7 = t7 + z5;
                    int z7;
                    z7 = 1 + (z6+1)/10;
                    cout << t7 << setw(4+schedule[z5][z6]->get_no().size()) << schedule[z5][z6]->get_no()
                    << setw(8-schedule[z5][z6]->get_no().size()+schedule[z5][z6]->get_over().size())
                    << schedule[z5][z6]->get_over()
                    << setw(55-schedule[z5][z6]->get_over().size()+schedule[z5][z6]->get_to().size())
                    << schedule[z5][z6]->get_to()
                    << setw(19-schedule[z5][z6]->get_to().size()+z7) << z6+1 << endl;
                    t7.~Time();
                }
            }
        }
        for (unsigned int z5 = 0; z5 < ((t3.get_minuteOfDay()+wieVielMin)%1440); z5++)
        {
            for (unsigned int z6 = 0; z6 < numberOfPlatforms; z6++)
            {
                if (schedule[z5][z6] != nullptr)
                {
                    Time t7;
                    t7 = t7 + z5;
                    int z7;
                    z7 = 1 + (z6+1)/10;
                    cout << t7 << setw(4+schedule[z5][z6]->get_no().size()) << schedule[z5][z6]->get_no()
                    << setw(8-schedule[z5][z6]->get_no().size()+schedule[z5][z6]->get_over().size())
                    << schedule[z5][z6]->get_over()
                    << setw(55-schedule[z5][z6]->get_over().size()+schedule[z5][z6]->get_to().size())
                    << schedule[z5][z6]->get_to()
                    << setw(19-schedule[z5][z6]->get_to().size()+z7) << z6+1 << endl;
                    t7.~Time();
                }
            }
        }
        }
    }
};
Station::~Station()
{
    for (unsigned int zz5 = 0; zz5 < 1440; zz5++)
        {
            for (unsigned int zz6 = 0; zz6 < numberOfPlatforms; zz6++)
            {
                if (schedule[zz5][zz6] != nullptr)
                {
                    Time tt7;
                    tt7 = tt7 + zz5;
                    cout << endl << tt7;
                    cout << " platform " << zz6 << ": ";
                    schedule[zz5][zz6]->~Train();
                    tt7.~Time();
                }
            }
        }
    cout << endl << "schedule for DUISBURG MAIN TRAIN STATION completely deleted!" << endl;
}

int main()
{
    Station duisburg("Duisburg Hauptbahnhof");
    Train *sZug1 = new Train("S1", "Dortmund Hbf", "Muelheim(Ruhr) Styrum - Muelheim(Ruhr) - Essen");
    Train *sZug2 = new Train("S1", "Solingen Hbf", "Duisburg - Schlenk - Duesseldorf Flughafen");
    Train *sZug3 = new Train("S2", "Dortmund Hbf", "Oberhausen - Gelsenkirchen - Wanne - Eickel");
    Train *rZug1 = new Train("RE1", "Aachen Hbf", "Duesseldorf Flughafen - Duesseldorf - Koeln");
    Train *rZug2 = new Train("RE2", "Muenster Hbf", "Muelheim(Ruhr) - Essen - Gelsenkirchen");
    for (int k = 7; k < 1440;)
    {
        Time tSet(0,k);
        duisburg.addDeparture(tSet, 9, sZug1);
        k += 20;
        tSet.~Time();
    }
    for (int k = 15; k < 1440;)
    {
        Time tSet(0,k);
        duisburg.addDeparture(tSet, 5, sZug2);
        k += 20;
        tSet.~Time();
    }
    for (int k = 35; k < 1440;)
    {
        Time tSet(0,k);
        duisburg.addDeparture(tSet, 2, sZug3);
        k += 60;
        tSet.~Time();
    }
    for (int k = 22; k < 1440;)
    {
        Time tSet(0,k);
        duisburg.addDeparture(tSet, 4, rZug1);
        k += 60;
        tSet.~Time();
    }
    for (int k = 24; k < 1440;)
    {
        Time tSet(0,k);
        duisburg.addDeparture(tSet, 10, rZug2);
        k += 60;
        tSet.~Time();
    }
    do
    {
        cout << endl << "0 end" << endl << "1 schedule train" << endl << "2 show schedule" << endl;
        int choiceIn;
        cin >> choiceIn;
        if (choiceIn == 0)
        {
            sZug1->~Train();
            sZug2->~Train();
            sZug3->~Train();
            rZug1->~Train();
            rZug2->~Train();
            return 0;
        }
        else if (choiceIn == 1)
        {
            cout << "time of departure? ";
            Time neuTime;
            cin >> neuTime;
            cout << "platform? ";
            int neuPlat;
            cin >> neuPlat;
            cout << "train? ";
            string neuNo, neuTo, neuOver;
            if ( cin.peek() == '\n' ) //The program skipped one line! Using getline(), sometimes this happens!
                cin.ignore();         //This is used to solve the problem.
            getline(cin, neuNo);
            cout << "to? ";
            getline(cin, neuTo);
            cout << "over? ";
            getline(cin, neuOver);
            Train *neuZug = new Train(neuNo, neuTo, neuOver);
            duisburg.addDeparture(neuTime, neuPlat, neuZug);
            neuZug->~Train();
            neuTime.~Time();
        }
        else if (choiceIn == 2)
        {
            cout << endl << "show departures starting at? ";
            Time choiceTime;
            cin >> choiceTime;
            cout << endl << "for how many next minutes? ";
            unsigned int choiceNextMin;
            cin >> choiceNextMin;
            duisburg.showDeparture(choiceTime, choiceNextMin);
        }
        else
        {
            cout << "wrong choice!" << endl << "Try again!" << endl;
        }
    } while (0 != 1);
}
