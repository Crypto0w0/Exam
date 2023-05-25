#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

bool compPair(const pair<string, int> &l, const pair<string, int> &r){
    if (l.second != r.second) {
        return l.second > r.second;
    }
    return l.first > r.first;
}

bool compInt(const int &l, const int &r){
    return l > r;
}

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
    string GetName() const{
        return name;
    }
    string GetSurname() const{
        return surname;
    }
    void Print(){
        cout << "Name:" << name << " " << surname << endl;
    }
    friend ostream& operator<<(ostream& o, const Person& p){
        o << p.GetName() << endl;
        return o;
    }
};

class MoneyStorage{
    int ballance;
    Person owner;
    map<string, int> chategories;
    map<string, int>::iterator i;
    // Shopping, Entertainment, Restaurant, Taxi
    vector<int> purchases;
public:
    MoneyStorage(){
        ballance = 0;
        chategories["Shopping"] = 0;
        chategories["Entertainment"] = 0;
        chategories["Restaurant"] = 0;
        chategories["Taxi"] = 0;
    }
    MoneyStorage(int b, Person p){
        ballance = b;
        owner = p;
    }
    MoneyStorage(Person p){
        ballance = 0;
        owner = p;
    }
    MoneyStorage(MoneyStorage& ms){
        ballance = ms.ballance;
        owner = ms.owner;
        chategories["Shopping"] = ms.chategories["Shopping"];
        chategories["Entertainment"] = ms.chategories["Entertainment"];
        chategories["Restaurant"] = ms.chategories["Restaurant"];
        chategories["Taxi"] = ms.chategories["Taxi"];
    }
    void SetBallance(int b){
        ballance = b;
    }
    int GetBallance(){
        return ballance;
    }
    void SetOwner(Person p){
        owner = p;
    }
    Person GetOwner(){
        return owner;
    }
    virtual void Print(){
        owner.Print();
        cout << "Current ballance: " << ballance << endl;
    }
    void AddBallance(){
        int val;
        cout << "Enter how much money do want to add to your ballance: ";
        cin >> val;
        ballance += val;
    }
    void Purchase(){
        int num;
        cout << "Enter how much money do want to purchase: ";
        cin >> num;
        if (num > ballance || num < 0){
            cout << "Error, not enought money\n";
            return ;
        }
        else ballance -= num;
        string ans;
        cout << "Enter in what chateghoty you want to buy smth:\n";
        cout << "(Shopping, Entertainment, Restaurants, Taxi)\n";
        cin >> ans;
        chategories[ans] += num;
        purchases.push_back(num);
        
    }
    void TOP3categories(){
        cout << "Top 3 chategories:\n";
        vector<pair<string, int>> v;
        copy(chategories.begin(), chategories.end(), back_inserter<vector<pair<string, int>>>(v));
        sort(v.begin(), v.end(), compPair);
        int n = 0;
        for (auto const &el : v) {
            if (n < 3){
                cout << n + 1 << ": " << el.first << " - " << el.second << endl;
                n++;
            }
        }
    }
    void TOP3purchases(){
        cout << "Top 3 purchases:\n";
        sort(purchases.begin(), purchases.end(), compInt);
        int n = 0;
        for (auto const &el : purchases) {
            if (n < 3){
                cout << n + 1 << ": " << el << endl;
                n++;
            }
        }
    }
    void AllCategories(){
        cout << "All chategories:\n";
        for(i = chategories.begin(); i != chategories.end(); i++){
            cout << (*i).first << " " << (*i).second << endl;
        }
    }
    void AllPurchases(){
        cout << "All purchases:\n";
        int n = 0;
        for (auto const &el : purchases) {
            cout << n + 1 << ": " << el << endl;
            n++;
        }
    }
};

class Card : public MoneyStorage{
    string number;
    string CVV;
public:
    virtual ~Card(){
        delete this;
    }
    Card(){
        number = to_string(rand() % 9999999999999999 + 1000000000000000);
        CVV = to_string(rand() % 9999 + 100);
    }
    Card(Card& c){
        this->SetBallance(c.GetBallance());
        this->SetOwner(c.GetOwner());
        number = c.number;
        CVV = c.CVV;
    }
    string GetNum(){
        return number;
    }
    string GetCVV(){
        return CVV;
    }
    virtual void Print() = 0;
};

class DebitCard : public Card{
public:
    void Print(){
        cout << "Owner: " << this->GetOwner();
        cout << "Ballance: " << this->GetBallance();
        cout << "Number: " << this->GetNum();
        cout << "CVV: " << this->GetCVV();
    }
};

class CreditCard : public Card{
public:
    void Print(){
        cout << "Owner: " << this->GetOwner();
        cout << "Ballance: " << this->GetBallance();
        cout << "Number: " << this->GetNum();
        cout << "CVV: " << this->GetCVV();
    }
    CreditCard(int b){
        this->SetBallance(b);
    }
};

class Wallet{
    vector<Card*> cards;
public:
    ~Wallet(){
        for (Card* el : cards){
            delete el;
        }
    }
    void NewCard(Person p){
        int ans;
        cout << "What type of card do you want to add? (1 - Debit, 2 - Credit)";
        cin >> ans;
        if (ans == 1){
            DebitCard* c = new DebitCard;
            cards.push_back(c);
            cout << "Number of your card: " << c->GetNum() << endl;
            cout << "CVV of your card: " << c->GetCVV() << endl;
            c->SetOwner(p);
        }
        else if (ans == 2){
            int m;
            cout << "Add a credit: ";
            cin >> m;
            CreditCard* c = new CreditCard(m);
            cards.push_back(c);
            cout << "Number of your card: " << c->GetNum();
            cout << "CVV of your card: " << c->GetCVV();
            c->SetOwner(p);
        }
    }
    void Print(){
        int i = 1;
        for (Card* el : cards){
            cout << "Card number " << i;
            el->Print();
        }
    }
    Card* Find(string n, string cvv){
        for (Card* el : cards){
            if (el->GetNum() == n && el->GetCVV() == cvv) return el;
        }
        cout << "Error";
        return nullptr;
    }
};

void Menu(){
    cout << "Welcome to the Banking App!\n";
    cout << "You need to create a wallet anyway ;)\n";
    string n;
    string sn;
    Wallet w;
    cout << "Enter your name: ";
    cin >> n;
    cout << "Enter your surname: ";
    cin >> sn;
    Person p(n, sn);
    w.NewCard(p);
    string cvv;
    Card* current;
    cout << "Enter thr number of the card you want to work with (16 nums): ";
    cin >> n;
    cout << "Enter the CVV of the card you want to work with (3-4 nums): ";
    cin >> cvv;
    current = w.Find(n, cvv);
    if (current != nullptr){
        while(true){
            int ans;
            cout << "What do you want to do?\n";
            cout << "(1 - Add a new Credit/Debit Card in your Wallet, 2 - Purchase from a Card, 3 - Add Money on the ballence of a Card, 4 - get top 3 purchases from a card, 5 - get top 3 chategories from a card), 6 - get all Purchases, 7 - get all Chategories, 8 - Show Card's Data, 9 - Change Card\n";
            cin >> ans;
            if (ans == 1) w.NewCard(p);
            else if (ans == 2) current->Purchase();
            else if (ans == 3) current->AddBallance();
            else if (ans == 4) current->TOP3purchases();
            else if (ans == 5) current->TOP3categories();
            else if (ans == 6) current->AllPurchases();
            else if (ans == 7) current->AllCategories();
            else if (ans == 8) current->Print();
            else if (ans == 9){
                cout << "Enter thr number of the card you want to work with (16 nums): ";
                cin >> n;
                cout << "Enter the CVV of the card you want to work with (3-4 nums): ";
                cin >> cvv;
                current = w.Find(n, cvv);
            }
            else cout << "Error";
        }
    } else cout << "Error. No such Card";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Menu();
}
