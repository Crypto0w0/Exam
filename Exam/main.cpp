#include <iostream>
using namespace std;

class Person{
    string name;
    string surname;
public:
    Person(){
        name = " ";
        surname = " ";
    }
    Person(string n, string s){
        name = n;
        surname = s;
    }
    Person(Person& p){
        name = p.name;
        surname = p.surname;
    }
    Person& operator=(Person& p){
        name = p.name;
        surname = p.surname;
        return *this;
    }
    void Print(){
        cout << "Name:" << name << " " << surname << endl;
    }
};

class MoneyStorage{
    int ballance;
    Person owner;
public:
    MoneyStorage(){
        ballance = 0;
    }
    MoneyStorage(int b, Person p){
        ballance = b;
        owner = p;
    }
    MoneyStorage(MoneyStorage& ms){
        ballance = ms.ballance;
        owner = ms.owner;
    }
    void Print(){
        owner.Print();
        cout << "Current ballance: " << ballance << endl;
    }
};

int main() {
    Person tom("Tom", "Shelby");
    MoneyStorage ms(5000, tom);
    ms.Print();
}
