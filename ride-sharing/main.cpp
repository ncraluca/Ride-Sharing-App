#include <iostream>
#include<cstring>
#include <string>
#include<vector>
#include <ctime>
#include <limits>
#include<algorithm>
#include<memory>
#include <random>

using namespace std;

// de aici incepe proiectul

//clasa template
template <typename T>
class Container {
private:
    vector<T> elements;

public:
    void addElement(const T& element) {
        elements.push_back(element);
    }

    void removeElement(const T& element) {
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    }

    void clear() {
        elements.clear();
    }

    int getSize() const {
        return elements.size();
    }

    T getElementAt(int index) const {
        if (index < 0 || index >= elements.size()) {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }
};



//interfata
class IOinterface{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class Vehicle{
protected:
    string marca;
    string model;
    string culoare;
public:
    Vehicle(string ma, string mo, string c): marca(ma), model(mo), culoare(c){}
    virtual ~Vehicle(){}
    //virtual ostream& operator<<(ostream& os) {
    //}

    virtual double getCost() = 0; // metoda pur virtuala, va fi implementata in clasele derivate
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
    os << "Marca: " << v.marca << ", Model: " << v.model << ", Culoare: " << v.culoare;
    return os;
}

};


class Bike : public Vehicle {
public:
    Bike(string ma, string mo, string c) : Vehicle(ma, mo, c) {}
    ~Bike() {}

    double getCost() override { return 2.5; } // pretul pentru o cursa cu bicicleta este de 2.5 lei pe km

};

class Scooter : public Vehicle {
public:
    Scooter(string ma, string mo, string c) : Vehicle(ma, mo, c) {}
    ~Scooter() {}

    double getCost() override { return 1.5; } // pretul pentru o cursa cu trotineta este de 1.5 lei pe km

};


enum class tipul_masinii{
        inchiriata, proprie
};
class Car: public Vehicle{
private:
    string nr_de_inmatriculare;
    int nr_locuri_libere;
    tipul_masinii tipul_masinii_;
    bool in_cursa;

public:

    //constructori cu parametri, liste de initializare
    Car(string ma, string mo, string c, string nr_de_inm, int nr_l_l, tipul_masinii T) : Vehicle(ma, mo, c), nr_de_inmatriculare(nr_de_inm), nr_locuri_libere(nr_l_l), tipul_masinii_(T), in_cursa(false){}
    ~Car(){}
    //metode
    double getCost() override
    {
        return 5;
    } // pretul pentru o cursa cu masina este de 5 lei pe km

    void start_cursa() { in_cursa = true; }
    void stop_cursa() { in_cursa = false; }

    //setteri

    void nr_de_inmatriculare_setter(string nr_de_inm){
        nr_de_inmatriculare = nr_de_inm;
    }

    void nr_locuri_libere_setter(int nr_l_l){
        nr_locuri_libere = nr_l_l;
    }

    void tipul_masinii_setter(tipul_masinii t_m){
        tipul_masinii_ = t_m;
    }

    void in_cursa_setter(bool in_cursa){
        this->in_cursa = in_cursa;
    }

    //getteri
    const string get_marca() const
    {
        return marca;
    }
    const string get_model() const{
        return model;
    }

    const string get_culoare() const{
        return culoare;
    }

    //trimit o copie a valorii din adresa
    //operatorul de deferentiere imi ia valoarea din adresa care face trimitere catre o zona de memorie
    const string get_nr_de_inmatriculare() const{
        return nr_de_inmatriculare;
    }

    int get_nr_locuri_libere()const{
        return nr_locuri_libere;
    }

    tipul_masinii get_tipul_masinii_(){
        return tipul_masinii_;
    }


    //supraincarcarea operatorului de afisare
    friend ostream& operator<<(ostream& os, const Car& c) {
            os << c.marca << " " << c.model<<", numar de inmatriculare: "<<c.nr_de_inmatriculare<< ", culoare: " << c.culoare;
            os << ", locuri libere: " << c.nr_locuri_libere;
            return os;
        }
    // 1 polimorfism daca dau cout


};
//partea a 3 a


class WorkHours {
private:
    int ore_pe_zi[7];
public:
    WorkHours() {
        for (int i = 0; i < 7; i++) {
            ore_pe_zi[i] = 0;
        }
    }

    void set_ore(int zi, int ora_start, int ora_final) {
        ore_pe_zi[zi] = (ora_final - ora_start)/60; //transformate in minute
    }

    void add_ore(int zi, int nr_ore)
    {
        ore_pe_zi[zi] = nr_ore;
    }

    int get_total_ore() {
        int total_ore = 0;
        for (int i = 0; i < 7; i++) {
            total_ore += ore_pe_zi[i];
        }
        return total_ore;
    }

    //functie care calculeaza numarul de ore muncite zilnic in medie intr-o saptamana
    double getAverageHoursPerDay() {
        return static_cast<double>(get_total_ore()) / 7;
    }

    //functie care returneaza numarul total de ore intr-o saptamana (calcule facute pentru saptamana anterioara)
    double getAverageHoursPerWeek() {
        return static_cast<double>(get_total_ore());
    }
};

class Person{
    string nume;
    string prenume;
    int age;
public:
    Person(string n, string p, int a): nume(n), prenume(p), age(a){}
    void set_nume( string n)
    {
        nume = n;
    }
    void set_prenume(string p)
    {
        prenume = p;
    }
    void set_age(int a)
    {
        age = a;
    }

    string get_nume() const
    {
        return nume;
    }
    string get_prenume() const
    {
        return prenume;
    }
    int get_age()
    {
        return age;
    }
    virtual ~Person(){}
    void printData()
	{
		cout << "Nume: " << nume << endl;
		cout << "Prenume: " << prenume << endl;
		cout<< "Varsta: "<< age<<endl;
	}
};

class PersonList {
protected:
    vector<shared_ptr<Person>> persons;

public:
    PersonList() {}

    /*
    virtual ~PersonList() {
        for (int i = 0; i < persons.size(); i++) {
            delete persons[i];
        }
    }
    */
    void add_candidate(shared_ptr<Person> e) {
        persons.push_back(e);
    }


    void remove_candidate(shared_ptr<Person> e) {
        for (int i = 0; i < persons.size(); i++) {
            if (persons[i] == e) {
                persons.erase(persons.begin() + i);
                break;
            }
        }
    }

    vector<shared_ptr<Person>> get_persons(){
        return persons;
    }

};

class VectorDeDouble: private vector<double>{
public:
    VectorDeDouble() : vector<double>(7, 0) {}
    using vector<double>::operator[]; // permite accesul la operatorul [] al vectorului
    using vector<double>::size;

};

class Salary_Employee: public IOinterface{
private:
    VectorDeDouble venit_zilnic;
    double salariu;
public:
    Salary_Employee(): venit_zilnic(), salariu(0.0){}
    Salary_Employee(VectorDeDouble v_z): venit_zilnic(v_z){}
    Salary_Employee(double s): salariu(s){}
    Salary_Employee(VectorDeDouble v_z, double s): venit_zilnic(v_z), salariu(s){}

    ostream& afisare(ostream& out) const
    {
        for (int i=0; i<venit_zilnic.size(); i++)
            out<<"venit: "<<this->venit_zilnic[i]<<"\n";
        return out;
    }
    istream& citire(istream& in) // implementation of citire() function
    {
        // read input from stream `in` and store it in the object's member variables
        for (int i=0; i<venit_zilnic.size(); i++)
            in >> venit_zilnic[i];
        in >> salariu;
        return in;
    }
    double calculeaza_salariu() {
        salariu = 0;
        for (int i = 0; i < 7; i++) {
            salariu += venit_zilnic[i];
        }
        return salariu; // un angajat lucreaza 7 zile pe saptamana
    }

    void adauga_venit(double venit, int zi) {
        venit_zilnic[zi] += venit;
    }

    double get_salariu() {
        return salariu;
    }
    VectorDeDouble get_venit_zilnic() const {
        return venit_zilnic;
    }

};

class Employee: public Person{
private:
    string data_angajare;
    Salary_Employee salariu;

public:
    Employee(string n, string p, int a): Person(n, p, a){}
    Employee(string n, string p, int a,  Salary_Employee s): Person(n, p,a), salariu(s){}
    Employee(string n, string p, int a, string d_a): Person(n, p, a), data_angajare(d_a){}
    Employee(string n, string p, int a, Salary_Employee s, string d_a): Person(n, p, a), salariu(s), data_angajare(d_a){}
    virtual void nr_abateri(){}
    void set_salariu(Salary_Employee s)
    {
        salariu = s;
    }
    void set_data_angajare(string data_angajare){
        data_angajare = data_angajare;
    }

    string get_nume() const{
        return Person::get_nume();
    }
    string get_prenume() const{
        return Person::get_prenume();
    }
    virtual double get_salariu(){
        return salariu.get_salariu();
    }
    virtual string get_data_angajare() const{
        return data_angajare;
    }
    bool operator<(const Employee& a) const {
        return get_nume() < a.get_nume();
    }
    void printData()
	{
		cout << "Nume: " << Person::get_nume() << endl;
		cout << "Prenume: " << Person::get_prenume() << endl;
		cout <<"Varsta: "<< Person::get_age() <<endl;
	}



};

class EmployeeList {
protected:
    vector<Employee*> employees;

public:
    EmployeeList() {}

    virtual ~EmployeeList() {
        for (int i = 0; i < employees.size(); i++) {
            delete employees[i];
        }
    }

    void add_employee(Employee* e) {
        employees.push_back(e);
    }

    void remove_employee(Employee* e) {
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i] == e) {
                employees.erase(employees.begin() + i);
                break;
            }
        }
    }
    Employee* find_employee(const string& firstName, const string& lastName)
    {
        auto searchEmployee = [](const Employee* e, const string& firstName, const string& lastName){
            return e->get_nume() == firstName && e->get_prenume() == lastName;
        };

        auto it = std::find_if(employees.begin(), employees.end(), [&](Employee* e){
            return searchEmployee(e, firstName, lastName);
        });

        if (it != employees.end()) {
            // angajatul a fost gasit
            return *it;
        } else {
            // angajatul nu a fost gasit
            return nullptr;
        }
    }

    vector<Employee*> get_employees(){
        return employees;
    }

    void sortare_dupa_nume() {
        std::sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
            return *a < *b;
        });
    }

    void sortare_dupa_salariu(bool crescator = true) {
        if (crescator) {
            std::sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
                return a->get_salariu() < b->get_salariu();
            });
        } else {
            std::sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
                return a->get_salariu() > b->get_salariu();
            });
        }
    }

    /*
    friend ostream& operator<<(ostream& os, vector<Employee*>& c) {
            for (int i = 0; i < employees.size(); i++) {
                os << employees[i]<< endl;
            }
            return os;
        }

    */

};
class PriceRide{
protected:
    unique_ptr<Vehicle> vehicle;
    double pret_cursa;

public:
    PriceRide(){}
    PriceRide(unique_ptr<Vehicle> v, double p_c) : vehicle(move(v)), pret_cursa(p_c) {}
    PriceRide(double p_c): pret_cursa(p_c){}
    double calculeaza_pret(double distanta){
        pret_cursa = vehicle->getCost() * distanta;
        return pret_cursa;
    }
    void set_pret_cursa(double p_c)
    {
        pret_cursa = p_c;
    }
    double get_pret_cursa(){
        return pret_cursa;
    }
    ~PriceRide(){}
};


class User: public IOinterface {
protected:
    string username;
    string parola;
    static int contor; //cati useri are aplicatia
protected:
    istream& citire(istream& in)
    {
        in>>this->username;
        in>>this->parola;
    }
    ostream& afisare(ostream& out) const
    {
        out<<"Username: "<<this->username<<"\n";
        out<<"Parola: "<<this->parola<<"\n";
    }

public:
    User(){contor++;}
    User(string u, string p) : username(u), parola(p) {contor++;}

    virtual ~User() {}

    virtual string get_Username() const {
        return username;
    }
    virtual string get_Parola() const {
        return parola;
    }

    virtual bool verificaParola(string p) const {
        return parola == p;
    }
    static int getCount() { // metoda statică pentru a obține numărul de instanțe
        return contor;
    }
    void set_count(int c)
    {
        contor = c;
    }
};
int User::contor=0;

class Driver: public User, public Employee{
    //nume, prenume, rating sofer, salariu(calculat dupa o formula in functie de orele lucrate, din clasa salary), masina(din clasa car)
private:
    double rating;
    Car* masina;

public:
    //constructor cu parametru, lista de initializare
    Driver(string u, string pw, string n, string p, double s, double r, Car* m) : User(u, pw), Employee(n, p, s), rating(r), masina(m) {}
    Driver(string u, string pw, string n, string p, double s, double r) : User(u, pw), Employee(n, p, s), rating(r) {}

    virtual ~Driver(){}


    //supraincarcare =
    Driver& operator=(const Driver& other) {
        if (this != &other) {
            Employee::operator=(other);
            rating = other.rating;
            masina = other.masina;
        }
        return *this;
    }


    //setteri
    void set_salariu(Salary_Employee s)
    {
       Employee::set_salariu(s);
    }

    void rating_setter(double r){
        rating = r;
    }


    void masina_setter(Car* m){
        masina = m;
    }


    //getteri

    string get_nume()const{
        return Person::get_nume();
    }
    string get_prenume() const{
        return Person::get_prenume();
    }
    double rating_get()const{
        return rating;
    }

    double get_salariu(){
        return Employee::get_salariu();
    }

    const Car masina_get() const{
        return *masina;
    }
    static int get_contor(){
        return User::contor;
    }
    void set_contor(int c){
        User::set_count(c);
    }

    friend ostream& operator<<(ostream& os, const Driver& d) {
            os << d.get_nume() << " " <<d.get_prenume() << ", Rating: " << d.rating;
            os<< endl;
            return os;
        }

    //idee: calculez nr de zile de cand e angajat un sofer- date de intrare: de tip char--> data inceput, data curenta

};
class DriverList {
protected:
    vector<Driver*> drivers;

public:
    DriverList(){}
    virtual ~DriverList() {
        for (int i = 0; i < drivers.size(); i++) {
            delete drivers[i];
        }
    }

    void add_driver(Driver* e) {
        drivers.push_back(e);
    }

    void remove_driver(Driver* e) {
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers[i] == e) {
                drivers.erase(drivers.begin() + i);
                break;
            }
        }
        int c = Driver::getCount();
        c--;
        e->set_contor(c);
    }

    Driver* get_random_driver() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, drivers.size() - 1);
        int randomIndex = dist(gen);
        return drivers[randomIndex];
    }

    vector<Driver*> get_drivers() const{
        return drivers;
    }

};

class Client : public User{
private:
    string nume;
    string prenume;
    int varsta;

public:
    Client(string u, string p, string n, string pr) : User(u, p), nume(n), prenume(pr) {}
    Client(string u, string p, string n, string pr, int v) : User(u, p), nume(n), prenume(pr), varsta(v) {}

    virtual ~Client() {}

    void set_nume(string s)
    {
        nume = s;
    }
    void set_prenume(string p)
    {
        prenume = p;
    }
    void set_varsta(int v)
    {
        varsta = v;
    }

    virtual string get_nume() const {
        return nume;
    }

    virtual string get_prenume() const {
        return prenume;
    }
    virtual int get_varsta() const {
        return varsta;
    }
    istream& citire(istream& in)
    {
        this->User::citire(in);
    }
    ostream& afisare(ostream& out)
    {
        out<<this->get_nume()<< " "<<this->get_prenume();
        return out;
    }
};

/*
// definirea altei excepții personalizate
class RideProcessingException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Comanda a fost deja procesata o data, nu poate fi procesata din nou.";
    }
};

// definirea unei excepții personalizate
class RideCanceledException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Comanda nu mai poate fi procesata deoarece a fost amanata deja.";
    }
};

class RideAlreadyCanceledException : public exception {
public:
    virtual const char* what() const throw() {
        return "Calatoria a fost deja anulata, nu o puteti anula din nou.";
    }
};
*/

enum class RideStatus { ACTIVE, CANCELED, COMPLETED };

class Ride: public IOinterface{
private:
    int id;
    RideStatus status;
    double distanta;
    string ora_comenzii;
    string ora_preluare;
    string ora_sosire;
    string loc_preluare;
    string destinatie;
public:
    Ride(int idd) : id(idd), status(RideStatus::ACTIVE) {}
    Ride(int idd, double d, string o_c, string o_p, string o_s, string l_p, string de): id(idd), distanta(d), ora_comenzii(o_c), ora_preluare(o_p), ora_sosire(o_s), loc_preluare(l_p), destinatie(de){}

    /*
    void processRide() {
        if (status == RideStatus::CANCELED) {
            throw RideCanceledException();
        } else if (status == RideStatus::COMPLETED) {
            throw RideProcessingException();
        } else {
            status = RideStatus::COMPLETED;
        }
    }

    void cancelRide() {
        if (status == RideStatus::CANCELED) {
            throw RideAlreadyCanceledException();
        } else {
            status = RideStatus::CANCELED;
        }
    }
    */
    // getteri
    RideStatus getRideStatus() const {
        return status;
    }
    int get_id() const{
        return id;
    }
    double get_distanta(){
        return distanta;
    }
    string get_ora_comenzii() {
        return ora_comenzii;
    }
    string get_ora_preluare()
    {
        return ora_preluare;
    }
    string get_ora_sosire()
    {
        return ora_sosire;
    }
    string get_loc_preluare()
    {
        return loc_preluare;
    }
    string get_destinatie()
    {
        return destinatie;
    }

    //setteri
    void set_ride_status(RideStatus s)
    {
        status = s;
    }

    //citire interfata
    istream& citire(istream& in)
    {
        cout<<"Care este locul dvs. de preluare?\n";
        in>>loc_preluare;
        cout<<"Unde doresti sa ajungi?\n";
        in>>destinatie;
        cout<<"Introdu nr. de km ai cursei.\n";
        in>>distanta;
        return in;

    }

    ostream& afisare(ostream& out) const
    {
        out<<loc_preluare;
        return out;
    }

};

class Manager : public User, public PersonList, public EmployeeList {
private:
    static Manager* instance;

    Manager(string u, string pw) : User(u, pw), PersonList() {}
    //constructor privat de copiere
public:
    static Manager* getInstance(string u, string pw) {
        if (!instance) {
            instance = new Manager(u, pw);
        }
        return instance;
    }

    void angajeaza(shared_ptr<Person> e) {
        PersonList::add_candidate(e);
    }

    void concediaza(Employee* e) {
        EmployeeList::remove_employee(e);
    }

    vector<Employee*> get_angajati() {
        return EmployeeList::get_employees();
    }

    istream& citire(istream& in) {
        this->User::citire(in);
    }
};
Manager* Manager::instance = nullptr;

bool containsOnlyLetters(std::string const &str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
        std::string::npos;
}



// --------------MENIU
void displaymenu()
{
    cout<<"========================================================== \n";
    cout<<" \t\tBine ai venit pe aplicatia noastra \t \n ";
    cout<<"========================================================== \n";
    cout<<"Ce tip de utilizator sunteti? Alegeti o optiune (1-3 sau q):\n";
    cout<<" 1.Manager\n";
    cout<<" 2.Sofer\n";
    cout<<" 3.Client \n";
    cout<<" q.Inchidere aplicatie \n";
}
void displaymanager()
{
    cout<<"Alegeti o optiune (1-5 sau q):\n";
    cout<<"1.Lista cu cereri angajari.\n";
    cout<<"2.Lista cu angajatii curenti.\n";
    cout<<"3.Lista cu cereri de concediu.\n";
    cout<<"4.Concediere angajati.\n";
    cout<<"5.Detaliile despre un angajat.\n";
    cout<<"q.Delogare din cont.\n";
}

void displaysofer()
{
    cout<<"Alegeti o optiune(1-7 sau q):\n";
    cout<<"1. Statistici salariu pe saptamana anterioara.\n";
    cout<<"2. Numar de ore lucrate in aceasta saptamana.\n";
    cout<<"3. Start lucru.\n";
    cout<<"4. Stop lucru.\n";
    cout<<"5. Istoric curse.\n";
    cout<<"6. Despre mine.\n";
    cout<<"7. Cerere concediu.\n";
    cout<<"q. Delogare din cont.\n";
}

void displayclient()
{
    cout<<"Alegeti o optiune(1-7 sau q):\n";
    cout<<"1. Doresc o cursa.\n";
    cout<<"2. Doresc sa inchiriez o trotineta.\n";
    cout<<"3. Doresc sa inchiriez o bicicleta.\n";
    cout<<"4. Istoric curse.\n";
    cout<<"5. Despre noi.\n";
    cout<<"6. Doresc sa ma angajez.\n";
    cout<<"7. Despre mine.\n";
    cout<<"q. Doresc sa ma deloghez din cont.\n";
}
void validate_varsta() {
  int varstaclient;
  bool valid_input = false;
  while (!valid_input) {
    try {
      cout<<"Varsta dvs.: ";
      if (!(cin >> varstaclient)) {
        throw "Tip de date introdus gresit!\n";
      }
      valid_input = true;
    } catch (const char* msg) {
      cerr << msg << endl;
      cin.clear(); // săptămână erorii
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorăm restul liniei
    }
  }
}

void validate_nume() {
  string numenou;
  bool valid_input1 = false;
  while (!valid_input1) {
    try {
      cout<<"Tastati noul nume: ";
      cin>>numenou;
      if (containsOnlyLetters(numenou)==0){
        throw "Tip de date introdus gresit!\n";
      }
      valid_input1 = true;
    } catch (const char* msg) {
      cerr << msg << endl;
      cin.clear(); // săptămână erorii
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorăm restul liniei
    }
  }
}
void validate_prenume()
{
    string prenumenou;
    bool valid_input12 = false;
    while (!valid_input12) {
    try {
    cout<<"Tastati noul prenume: ";
    cin>>prenumenou;
    if (containsOnlyLetters(prenumenou)==0){
    throw "Tip de date introdus gresit!\n";
    }
    valid_input12 = true;
    } catch (const char* msg) {
    cerr << msg << endl;
    cin.clear(); // săptămână erorii
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorăm restul liniei
    }
        }
}

// Funcție șablon pentru a număra un anumit tip de obiecte
template <typename T>
int countObjectsOfType(const T& container) {
    return container.getSize();
}

// Specializare a funcției șablon pentru clasa DriverList pentru a număra șoferii cu un anumit rating
template <>
int countObjectsOfType(const DriverList& driverList) {
    int count = 0;
    for (const auto& driver : driverList.get_drivers()) {
        if (driver->rating_get() >= 4.5) {  // Ratingul dorit, puteți înlocui cu valoarea dorită
            count++;
        }
    }
    return count;
}

int main()
{

    int ct1 = -1;
    int ct2=-1;
    int ct3 =-1;

    /*
    //unique_ptr
    unique_ptr<Vehicle> masina2 = make_unique <Car> ("Dacia", "Logan", "Albastru", "B112EXE", 4, tipul_masinii::proprie);
    unique_ptr<Vehicle> trotineta = make_unique <Scooter>("Kugoo", "G2", "Neagra");
    unique_ptr<Vehicle> bicicleta = make_unique <Bike> ("Pegas", "Retro20", "Rosie");
    if (Car* c = dynamic_cast<Car*>(masina2.get())) {
        cout << *c << endl;
    }
    else {
        cout << *masina2 << endl;
    }
    if (Scooter* c = dynamic_cast<Scooter*>(trotineta.get())) {
        cout << *c << endl;
    }
    else {
        cout << *trotineta << endl;
    }
    if (Bike* c = dynamic_cast<Bike*>(bicicleta.get())) {
        cout << *c << endl;
    }
    else {
        cout << *bicicleta << endl;
    }
    */
    //date salvate
    unique_ptr<Vehicle> masina2 = make_unique <Car> ("Dacia", "Logan", "Albastru", "B112EXE", 4, tipul_masinii::proprie);
    unique_ptr<Vehicle> trotineta = make_unique <Scooter>("Kugoo", "G2", "Neagra");
    unique_ptr<Vehicle> bicicleta = make_unique <Bike> ("Pegas", "Retro20", "Rosie");

    shared_ptr<Person> candidat1 = make_shared <Person>("Gogonel", "Bobu", 22);
    shared_ptr<Person> candidat2 = make_shared <Person>("nume2", "prenume2", 25);
    shared_ptr<Person> candidat3 = make_shared <Person>("nume3", "prenume3", 30);
    string username = "username";
    string password = "password";
    Manager* manager = Manager::getInstance(username, password);
    string user;
    string parola;
    string user2;
    string parola2;
    PersonList candidati;
    EmployeeList angajati;
    DriverList soferi;

    //pt sablon
    soferi.add_driver(new Driver("user1", "pass1", "John", "Doe", 1000.0, 4.5));
    soferi.add_driver(new Driver("user2", "pass2", "Alice", "Smith", 1200.0, 4.2));
    soferi.add_driver(new Driver("user3", "pass3", "Bob", "Johnson", 1500.0, 4.8));
    soferi.add_driver(new Driver("user4", "pass4", "Emma", "Davis", 1300.0, 4.5));
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());
    uniform_int_distribution<int> unif_dist(0, soferi.get_drivers().size() - 1);
    /*
     for (int i = 0; i < 7; ++i) {
        cout << unif_dist(gen) << " "; // pass the generator to the distribution.
    }
    */
    candidati.add_candidate(candidat1);
    candidati.add_candidate(candidat2);
    candidati.add_candidate(candidat3);
    Ride ride(123);

    int zi;
    int ore;
    double venit;
    WorkHours ore_muncite;
    VectorDeDouble venituri;
    double salariu;
    Salary_Employee angajat(venituri, salariu);

    string numeclient="Gogonel";
    string prenumeclient="Gogu";
    int varstaclient;
    Client client("userc", "passwordc", numeclient, prenumeclient);

    double pret =0.0;
    Container<Ride> rideContainer;

     //autentificare cont
    bool quit = false;  // Flag for quitting
    while(quit == false)
    {
        system("cls");
        displaymenu();
        char response;
        cin >> response;
        switch(response)
        {
            case '1' :
            {
                system("cls");
                cout << "Va rugam sa va autentificati cu contul dvs. de manager:" << endl;
                bool quit1 = false;
                while(quit1 == false)
                {
                    manager->citire(cin);
                    if("username"!= manager->get_Username())
                    {
                        system("cls");
                        cout<<"User incorect! Mai incercati inca o data.\n";
                    }
                    else
                    {
                        if(manager->verificaParola("password") == false)
                        {
                            system("cls");
                            cout<<"Parola incorecta! Mai incercati inca o data.\n";
                        }
                        else
                        {
                            system("cls");
                            cout<<"Bine ati venit, " << manager->get_Username()<< "!\n";
                            quit1 = true;

                        }

                    }
                }
                bool quit11 = false;
                while(quit11==false)
                {
                    system("cls");
                    displaymanager();
                    cin>>response;
                    switch(response)
                    {
                        case '1':
                        {
                            //int countPersons = countObjectsOfType(candidati);
                            //cout << "Numarul de persoane din lista: " << countPersons << endl;
                            cout<<"Lista de potentiali angajati: \n";
                            vector<shared_ptr <Person>> candidatii = candidati.get_persons();
                            system("cls");
                            char answer;
                            for (shared_ptr <Person> candidatt : candidatii)
                            {
                                cout<<"Accepti acest candidat?(y/n) \n";
                                candidatt->printData();
                                bool corect = false;
                                while(corect == false)
                                {

                                    cin>>answer;
                                    switch (answer)
                                    {
                                        case 'y':
                                        {
                                            candidatt->printData();
                                            manager->angajeaza(candidatt);
                                            system("cls");
                                            cout<<"A fost angajat cu succes.\n ";
                                            corect = true;
                                            time_t now = time(0);
                                            string dt = ctime(&now);
                                            Employee* angajatt = new Employee(candidatt->get_nume(), candidatt->get_prenume(), 0, dt);
                                            angajati.add_employee(angajatt);
                                            cout<<"Ce username doresti sa aiba angajatul? \n";
                                            cin>>user2;
                                            cout<<"Ce parola doresti sa aiba angajatul? \n";
                                            cin>>parola2;
                                            Driver* driver = new Driver(user2, parola2, angajatt->get_nume(), angajatt->get_prenume(), angajatt->get_salariu(), 0);
                                            soferi.add_driver(driver);
                                            candidati.remove_candidate(candidatt);
                                            system("cls");
                                            break;
                                        }
                                        case 'n':
                                        {
                                            candidatt->printData();
                                            cout<<"Nu a fost angajat.\n";
                                            corect = true;
                                            candidati.remove_candidate(candidatt);
                                            system("cls");
                                            break;
                                        }
                                        default: cout<<"Tasta incorecta. Mai incercati o data din optiunile: y/n\n";
                                    }

                                }
                            }

                            break;

                        }
                        case '2':
                        {
                            system("cls");
                            cout<<"Aplicatia are "<<User::getCount()<< " useri.\n";
                            bool sunt_doar_employee = true;
                            for (auto angajat : angajati.get_employees()) {
                                if (dynamic_cast<Employee*>(angajat) == nullptr) {
                                    sunt_doar_employee = false;
                                    break;
                                }
                            }

                            if (sunt_doar_employee) {
                                cout << "Toate variabilele din vector sunt de tip Employee*\n";
                            } else {
                                cout << "Vectorul de angajati contine si alte variabile in afara de Employee*\n";
                            }
                            bool quit112 = false;
                            while(quit112==false)
                            {
                                cout<<"Cum doresti sa vezi lista de angajati? Alege o optiune (1-3): \n";
                                cout<<"1.Sortata alfabetic\n";
                                cout<<"2.Sortata crescator dupa salariu\n";
                                cout<<"3.Sortata descrescator dupa salariu\n";
                                cout<<"q.Vreau inapoi in meniul principal\n";
                                char rasp;
                                cin>>rasp;
                                switch(rasp)
                                {
                                    case '1':
                                    {
                                        cout<<"Lista de angajati este: \n\n";
                                        angajati.sortare_dupa_nume();
                                        for (const auto& angajat : angajati.get_employees()) {
                                            cout << "Numele angajatului: "<< angajat->get_nume() << endl<< "Prenumele angajatului: " << angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<endl<<endl;
                                        }
                                        quit112 = true;
                                        system("pause");
                                        break;
                                    }
                                    case '2':
                                    {
                                        cout<<"Lista de angajati este: \n\n";
                                        angajati.sortare_dupa_salariu(true);
                                        for (const auto& angajat : angajati.get_employees()) {
                                            cout << "Numele angajatului: "<< angajat->get_nume() << endl<< "Prenumele angajatului: " << angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<endl<<endl;
                                        }
                                        quit112 = true;
                                        system("pause");
                                        break;
                                    }
                                    case '3':
                                    {
                                        cout<<"Lista de angajati este: \n\n";
                                        angajati.sortare_dupa_salariu(false);
                                        for (const auto& angajat : angajati.get_employees()) {
                                            cout << "Numele angajatului: "<< angajat->get_nume() << endl<< "Prenumele angajatului: " << angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<endl<<endl;
                                        }
                                        quit112 = true;
                                        system("pause");
                                        break;
                                    }
                                    case 'q':
                                    {
                                        quit112 = true;
                                        system("pause");
                                        break;
                                    }
                                    default:
                                    {
                                        cout << "Optiune invalida!"<< endl;
                                        system("pause");
                                    }

                                }
                            }
                            system("pause");
                            break;
                        }
                        case '3':
                        {
                            cout<<"va urma\n";
                            break;
                        }
                        case '4':
                        {
                            cout<<"Alege o optiune (y/n)\n";
                            char answer4;
                            for (const auto& angajat : angajati.get_employees()) {
                                cout<<"Doresti sa concediezi angajatul: ";
                                cout << angajat->get_nume() << " "<< angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<"?"<<endl<<endl;
                                bool corect4 = false;
                                while(corect4 == false)
                                {

                                    cin>>answer4;
                                    switch (answer4)
                                    {
                                        case 'y':
                                        {
                                            cout << angajat->get_nume() << " "<< angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<endl;
                                            manager->concediaza(angajat);
                                            angajati.remove_employee(angajat);

                                            for (const auto& sofer : soferi.get_drivers()) {
                                                string numee = sofer->get_nume();
                                                string prenumee = sofer->get_prenume();
                                                if(numee==angajat->get_nume() and prenumee==angajat->get_prenume())
                                                {
                                                    soferi.remove_driver(sofer);
                                                    break;

                                                }
                                            }

                                            cout<<"A fost concediat cu succes.\n";
                                            corect4 = true;
                                            break;
                                        }
                                        case 'n':
                                        {
                                            cout << angajat->get_nume() << " "<< angajat->get_prenume()<<endl
                                                <<"Data angajarii: "<< angajat->get_data_angajare() <<"Salariul angajatului din saptamana anterioara: "<<angajat->get_salariu()<<endl<<endl;
                                            cout<<"Nu a fost concediat.\n";
                                            corect4 = true;
                                            break;
                                        }
                                        default: cout<<"Tasta incorecta. Mai incercati o data din optiunile: y/n\n";
                                    }

                                }
                            }
                            break;
                        }
                        case '5':
                        {
                            cout<<"Ce angajat doresti sa vezi?\n Introdu numele si prenumele acestuia: \n";
                            string numeangajat;
                            string prenumeangajat;
                            cin>>numeangajat;
                            cin>>prenumeangajat;
                            Employee* foundEmployee = angajati.find_employee(numeangajat, prenumeangajat);
                            if (foundEmployee != nullptr) {
                                // afisati informatiile despre angajatul gasit
                                foundEmployee->printData();
                            } else {
                                // afisati un mesaj de eroare
                                cout << "Angajatul nu a fost gasit." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 'q':
                        {
                            quit11=true;
                            break;
                        }
                        default :
                        {
                            cout << "Optiune invalida!"<< endl;
                            system("pause");
                        }
                    }
                }
                break;
            }
            case '2' :
            {
                    cout << "Va rugam sa va autentificati cu contul dvs. de sofer:" << endl;
                    bool quit2 = false;
                    while(quit2 == false)
                    {
                        cin>> user2;
                        cin>> parola2;
                        string usercorect;
                        string parolacorecta;
                        for (const auto& sofer : soferi.get_drivers()) {
                                if(user2 == sofer->get_Username())
                                {
                                    usercorect = sofer->get_Username();
                                    break;
                                }
                            }
                        if(user2!= usercorect)
                            cout<<"User incorect! Mai incercati inca o data.\n";
                        else
                        {
                            for (const auto& sofer : soferi.get_drivers()) {
                                if(user2 == sofer->get_Username())
                                {
                                    usercorect = sofer->get_Username();
                                    if(sofer->verificaParola(parola2) == false)
                                    {
                                        cout<<"Parola incorecta! Mai incercati inca o data.\n";
                                    }
                                    else
                                    {
                                        cout<<"Bine ati venit, " << user2<< "!\n";
                                        system("pause");
                                        quit2 = true;

                                    }
                                    break;
                                }
                            }

                        }

                    }
                    bool quit12 = false;
                    while(quit12==false)
                    {
                        system("cls");
                        displaysofer();
                        cin>>response;
                        switch(response)
                        {
                            case '1':
                            {
                               cout<<"Salariul tau pe aceasta saptamana este: ";
                               for (const auto& sofer : soferi.get_drivers()) {
                                    if(user2 == sofer->get_Username())
                                    {
                                        cout<<sofer->get_salariu()<<" lei.\n";
                                        break;
                                    }
                                }
                                system("pause");
                               break;
                            }
                            case '2':
                            {
                               cout<<"Numarul de ore lucrate este:\n"<<ore_muncite.get_total_ore()<<endl;
                               system("pause");
                               break;
                            }
                            case '3':
                            {
                                cout<<"Ce zi a saptamanii este?\n 0.LUNI\n 1.MARTI \n 2.MIERCURI\n 3.JOI\n 4.VINERI\n 5.SAMBATA\n 6.DUMINICA\n";
                                cin>>zi;
                                cout<<"Cursele disponibile sunt:\n";
                                system("pause");
                                break;
                            }
                            case '4':
                            {
                                cout<<"Cate ore ai muncit?\n";
                                cin>> ore;
                                ore_muncite.add_ore(zi, ore);
                                cout<< "Numarul de ore a fost actualizat.\n";
                                cout<<"Care este venitul tau pe aceasta zi? \n";
                                cin>>venit;
                                angajat.adauga_venit(venit, zi);
                                salariu = angajat.calculeaza_salariu();
                                venituri = angajat.get_venit_zilnic();
                                for (const auto& sofer : soferi.get_drivers()) {
                                    string numee = sofer->get_nume();
                                    string prenumee = sofer->get_prenume();
                                    if(user2 == sofer->get_Username())
                                    {
                                        sofer->set_salariu(salariu);
                                        for (const auto& angajatt : angajati.get_employees()) {
                                            if( numee == angajatt->get_nume() and prenumee==angajatt->get_prenume())
                                            {
                                                angajatt->set_salariu(salariu);
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                system("pause");
                                }
                                cout<<"Veniturile tale pe aceasta saptamana: \n";
                                angajat.afisare(cout);
                                // calcularea salariului salariu = angajat.calculeaza_salariu();
                                //cout<<angajat.get_salariu();
                                system("pause");
                                break;
                            }
                            case '5': cout<<"va urma\n"; break;
                            case '6':
                            {
                                system("cls");
                                cout<<"==========================================================\n";
                                cout<<"     Detalii despre contul meu\n";
                                cout<<" ==========================================================\n";
                                for (const auto& sofer : soferi.get_drivers()) {
                                    if(user2 == sofer->get_Username())
                                    {
                                        cout << "Numele: "<< sofer->get_nume() << endl<< "Prenumele: " << sofer->get_prenume()<<endl
                                                <<"Salariul din saptamana anterioara: "<<sofer->get_salariu()<<endl<<"Rating-ul meu: "<<sofer->rating_get()<<endl<<endl;
                                        break;
                                    }
                                }
                                int countHighRatedDrivers = countObjectsOfType(soferi);
                                cout << "Number of drivers with rating 4.5 or higher: " << countHighRatedDrivers << endl;
                                system("pause");
                                break;
                            }
                            case '7': cout<<"va urma\n"; break;
                            case 'q':
                            {
                                quit12=true;
                                break;
                            }
                            default:
                                cout<<"Optiune invalida!"<<endl;

                        }

                    }

                    break;
            }
            case '3' :
            {
                cout << "Va rugam sa va autentificati cu contul dvs. de client:" << endl;
                bool quit3 = false;
                while(quit3 == false)
                {
                    client.citire(cin);
                    if("userc"!= client.get_Username())
                        cout<<"User incorect! Mai incercati inca o data.\n";
                    else
                    {
                        if(client.verificaParola("passwordc") == false)
                        {
                            cout<<"Parola incorecta! Mai incercati inca o data.\n";
                        }
                        else
                        {
                            cout<<"Bine ati venit, ";
                            client.afisare(cout);
                            cout<< "!\n";
                            system("pause");
                            quit3 = true;

                        }

                    }
                }
                bool quit31 = false;
                while(quit31 == false)
                {
                    system("cls");
                    displayclient();
                    cin>>response;
                    switch(response)
                    {
                        case '1':
                        {
                             bool quit311 = false;
                             while(quit311 == false)
                             {
                            ride.citire(cin);
                             //functionalitate unique ptr
                             unique_ptr<Vehicle> masina = make_unique <Car> ("BMW", "X3", "Rosu", "B112OOP", 3, tipul_masinii::inchiriata);
                             PriceRide pret_cursa(move(masina), pret);
                             double dist = ride.get_distanta();
                             pret = pret_cursa.calculeaza_pret(dist);
                             cout<<"Cursa o sa coste: "<<pret<<" lei.\n";
                             Ride ride1(ride.get_id(), dist, "19:00", "19:30", "20:00", ride.get_loc_preluare(), ride.get_destinatie());
                             rideContainer.addElement(ride1);
                             Ride firstRide = rideContainer.getElementAt(0);
                             //functionalitate clasa TEMPLATE
                             cout << "Detalii primul ride:\n";
                             cout << "ID: " << firstRide.get_id() << endl;
                             cout<<"Ora comenzii: "<< firstRide.get_ora_comenzii()<<endl;
                             cout<<"Ora preluarii: "<< firstRide.get_ora_preluare()<<endl;
                             cout<<"Ora sosirii: "<< firstRide.get_ora_sosire()<<endl;
                             cout <<"Distanta: " << firstRide.get_distanta() << endl;
                             cout<<"Loc preluare: "<<firstRide.get_loc_preluare()<<endl;
                             cout<<"Destinatie: "<<firstRide.get_destinatie()<<endl;
                             int ctmas = countObjectsOfType(rideContainer);
                             cout<<"Numar de masini disponibile: "<< ctmas<<endl;

                             cout<<"Cursa preluata de soferul: \n";
                             int random = unif_dist(gen);
                             int cntrandom = 0;
                             for (const auto& sofer : soferi.get_drivers()) {
                                    if(cntrandom == random)
                                    {
                                        cout << sofer->get_nume() << " " <<sofer->get_prenume()<<", rating: "<<sofer->rating_get()<<endl<<endl;
                                        break;
                                    }
                                    cntrandom++;
                                }
                            cout<<"E in regula cursa?\n(y/n)";
                            char raspp;
                            bool oki = false;
                            while(oki == false)
                            {
                                cin>>raspp;
                                switch(raspp)
                                {
                                    case 'y':
                                    {
                                        cout<<"Calatorie placuta!\n";
                                        oki = true;
                                        quit311 = true;
                                        system("pause");
                                        break;

                                    }
                                    case 'n':
                                    {
                                      cout<<"incearca o alta cursa! \n";
                                      oki = true;
                                      system("pause");
                                      break;
                                    }
                                    default:
                                    {
                                       cout<<"Optiune invalida!\n";
                                    }
                                }
                            }
                             }



                             system("pause");
                             break;
                        }
                        case '2': cout<<"va urma\n"; break;
                        case '3': cout<<"va urma\n"; break;
                        case '4': cout<<"va urma\n"; break;
                        case '5':
                        {
                            system("cls");
                            cout<<"==========================================================\n";
                            cout<<"     Regandim modul in care lumea se misca spre mai bine\n";
                            cout<<" ==========================================================\n";
                            cout<<"Miscarea este puterea noastra. Este ratiunea noastra de a fi. Ne curge prin vene.";
                            cout<<"Este motivul pentru care ne \nridicam din pat dimineata. Ne inspira sa regandim constant moduri mai bune de a ne misca. Pentru tine. ";
                            cout<<"Pentru \ntoate locurile unde vrei sa ajungi. Pentru toate lucrurile pe care vrei sa le obtii. Pentru toate modurile in \ncare vrei sa";
                            cout<<" faci bani. In intreaga lume. In timp real. Cu viteza incredibila a prezentului.\n";
                            cout<<"\n\n";
                            cout<<"==========================================================\n";
                            cout<<"     Mai mult decat curse\n";
                            cout<<" ==========================================================\n";
                            cout<<"Ajutam pasagerii sa ajunga din punctul A in punctul B, dar asta nu e tot. Ajutam oamenii sa comande ";
                            cout<<"mancare \nrapid si convenabil, inlaturam obstacolele din calea ingrijirii medicale, cream solutii noi ";
                            cout<<"pentru rezervarea \ntransporturilor de marfa si ajutam companiile sa le ofere angajatilor o experienta ";
                            cout<<"optima de transport. \nSi ajutam mereu soferii si curierii parteneri sa obtina venituri.\n\n";
                            system("pause");
                            break;
                        }
                        case '6':
                        {
                            system("cls");
                            cout<<"==========================================================\n";
                            cout<<"     Stabileste-ti propriul program\n";
                            cout<<" ==========================================================\n";
                            cout<<"Tu esti seful. Poti sa conduci oricand cu aplicatia noastra. \nStabileste-ti cum vrei programul de condus.\n\n";
                            cout<<"==========================================================\n";
                            cout<<"     Castiga bani dupa propriul program\n";
                            cout<<" ==========================================================\n";
                            cout<<"Cu cat conduci mai mult, cu atat castigi mai mult. Cand cererea \neste mai mare decat in mod normal, poti castiga mai mult.\n\n";
                             cout<<"==========================================================\n";
                            cout<<"     Lasa aplicatia sa te conduca\n";
                            cout<<" ==========================================================\n";
                            cout<<"Doar apasa un buton si porneste la drum. Vei primi indicatii pas \ncu pas, sugestii care sa te ajute sa castigi mai mult";
                            cout<<" si asistenta non-stop.\n\n";
                            system("pause");
                            system("cls");
                            cout<<"Spuneti-ne detaliile despre dvs, "<<client.get_nume()<<" "<<client.get_prenume()<<":\n";
                            bool valid_input = false;

                            while (!valid_input) {
                              try {
                                cout<<"Varsta dvs.: ";
                                if (!(cin >> varstaclient)) {
                                  throw "Tip de date introdus gresit!\n";
                                }
                                valid_input = true;
                              } catch (const char* msg) {
                                cerr << msg << endl;
                                cin.clear(); // săptămână erorii
                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorăm restul liniei
                              }
                            }
                            //validate_varsta();

                            client.set_varsta(varstaclient);
                            cout<<"De ce doriti sa va angajati?\n";
                            string motiv_angajare;
                            cin>>motiv_angajare;
                            system("cls");
                            bool quit6;
                            quit6=false;
                            char answer6;
                            while(quit6 == false)
                            {

                                cout<<"Doriti sa va modificati numele sau prenumele? Alegeti o optiune (y/n):\n";
                                cin>>answer6;
                                system("cls");
                                switch(answer6)
                                {
                                    case 'y':
                                    {
                                        quit6=true;
                                        cout<<"Ce doriti sa modificati?\n\n1.Nume\n2.Prenume\nq.M-am razgandit, vreau sa ma intorc in meniul principal.\n";
                                        char answer61;
                                        bool quit61;
                                        quit61 = false;
                                        while(quit61==false)
                                        {
                                            cin>>answer61;
                                            switch(answer61)
                                            {
                                                case '1':
                                                {
                                                    string numenou;
                                                    validate_nume();
                                                    cout<<"Numele a fost modificat cu succes!\n";
                                                    client.set_nume(numenou);
                                                    quit61=true;
                                                    cout<<"Doriti sa va modificati si prenumele?(y/n)\n";
                                                    char answer611;
                                                    bool quit611=false;
                                                    while(quit611==false)
                                                    {
                                                        cin>>answer611;
                                                        switch(answer611)
                                                        {
                                                            case 'y':
                                                            {
                                                                string prenumenou;
                                                                validate_prenume();
                                                                cout<<"Prenumele a fost modificat cu succes!\n";
                                                                client.set_prenume(prenumenou);
                                                                quit611=true;
                                                                break;
                                                            }
                                                            case 'n':
                                                            {
                                                                cout<<"Intoarcere la formular...\n";
                                                                system("cls");
                                                                quit611 =true;
                                                               break;
                                                            }
                                                            default:
                                                                cout<<"Optiune invalida!\n";

                                                        }
                                                    }
                                                    break;

                                                }
                                                case '2':
                                                {
                                                    string prenumenou;
                                                    validate_prenume();
                                                    cout<<"Prenumele a fost modificat cu succes!\n";
                                                    client.set_prenume(prenumenou);
                                                    quit61=true;
                                                    cout<<"Doriti sa va modificati si numele?(y/n)\n";
                                                    char answer611;
                                                    bool quit611=false;
                                                    while(quit611==false)
                                                    {
                                                        cin>>answer611;
                                                        switch(answer611)
                                                        {
                                                            case 'y':
                                                            {

                                                                string numenou;
                                                                validate_nume();
                                                                client.set_nume(numenou);
                                                                quit611=true;
                                                                break;
                                                            }
                                                            case 'n':
                                                            {
                                                                cout<<"Intoarcere la formular...\n";
                                                                system("cls");
                                                                quit611 =true;
                                                               break;
                                                            }
                                                            default:
                                                                cout<<"Optiune invalida!\n";

                                                        }
                                                    }
                                                    break;
                                                }
                                                case 'q':
                                                {
                                                    quit61= true;
                                                    break;
                                                }
                                                default:
                                                    cout<<"Optiune invalida!\n";

                                            }

                                        }
                                        break;
                                    }
                                    case 'n':
                                    {
                                        quit6=true;
                                        break;
                                    }
                                    default:
                                        cout<<"Optiune invalida!\n";
                                }

                            }
                            system("pause");
                            //system("cls");
                            if(varstaclient<18)
                            {
                                cout<<"\nNe pare rau, nu te poti angaja deoarece esti minor!\n\n";
                            }
                            else
                            {
                                shared_ptr <Person> candidat = make_shared <Person>(numeclient, prenumeclient, varstaclient);
                                candidati.add_candidate(candidat);
                                cout<<"\nFormularul de angajare a fost inregistrat!\n\n";

                            }
                            system("pause");
                            break;
                        }
                        case '7':
                        {
                            system("cls");
                            cout<<"==========================================================\n";
                            cout<<"     Detalii despre contul meu\n";
                            cout<<" ==========================================================\n";
                            cout<<"Numele: "<<client.get_nume()<<"\n";
                            cout<<"Prenumele: "<<client.get_prenume()<<"\n";
                            cout<<"Varsta: "<<client.get_varsta()<<"\n";
                            system("pause");
                            break;

                        }
                        case 'q':
                        {
                            quit31 = true;
                            break;
                        }
                        default :
                        {
                            cout << "Optiune invalida!"<< endl;
                            system("pause");
                        }
                    }

                }
                break;
            }
            case 'q' :
            {
                cout << "quitting menu" << endl;
                quit = true;
                break;
            }
            default :
            {
                cout << "Optiune invalida!"<< endl;
                system("pause");
            }
      }
   }

    return 0;

}
