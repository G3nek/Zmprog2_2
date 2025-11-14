//WEL24MX1S4
//Stanisław Wawryszuk
//14.11.2025
//Linux c++
//10.202.131.85

#include <iostream>
#include <string>

using namespace std;

class Kalkulator {
public:
    virtual int Działanie(int a, int b) = 0;
    virtual ~Kalkulator() {}
};

class Dodawanie : public Kalkulator {
public: 
    int Działanie(int a, int b) override {return a + b; }
};

class Odejmowanie : public Kalkulator {
public: 
    int Działanie(int a, int b) override {return a - b; }
};

class Mnożenie : public Kalkulator {
public: 
    int Działanie(int a, int b) override {return a * b; }
};

class Iloraz : public Kalkulator {
public: 
    int Działanie(int a, int b) override { return b == 0 ? 0 : a / b; }
};

class Kreator{
    Kalkulator* k;
public:
    Kreator(char t) : k(nullptr) {
        if(t=='d') k=new Dodawanie();
        else if(t=='o') k=new Odejmowanie();
        else if(t=='m') k=new Mnożenie();
        else if(t=='i') k=new Iloraz();
    }
    ~Kreator()  { delete k; }
    Kalkulator* Get() { return k; };
};

class Logger{
    string historia;

    Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
public: 
    static Logger& GetInstance()    {
        static Logger inst;
        return inst;
    }

    void Log(const string& wpis) {
        historia += wpis + "\n";
    }

    void Pokaz() {
        cout << historia;
    }
};
   

int main() {
    while(true){
        char t;
        int a, b;
        printf("Wpisz d dla dodawania, o dla odejmowania, m dla mnożenia, i dla ilorazu\n");
        cin >> t;

        if(t=='q') break;
        if(t=='h') {Logger::GetInstance().Pokaz(); continue;}

        printf("Wpisz dwie liczby a oraz b\n"); 
        cin >> a >> b;

        Kreator fabryka(t);
        Kalkulator* k = fabryka.Get();
        if(!k) { cout << "Brak takiego działania\n"; return 0; }

        int wynik = k->Działanie(a, b);
        string opis = to_string(a) + " ";
        if(t=='d') opis += "+ ";
        else if(t=='o') opis += "- ";
        else if(t=='m') opis += "* ";
        else if(t=='i') opis += "/ ";
        opis += to_string(b) + " = " + to_string(wynik);

        Logger::GetInstance().Log(opis);
    }
}
