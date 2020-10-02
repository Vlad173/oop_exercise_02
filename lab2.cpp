/**
 * Епанешников М80-206Б-19
 * Создать класс IPAddress для работы с адресом в интернет. Класс состоит из четырех чисел unsigned char (a,b,c,d). 
 * Реализовать арифметические операции сложения, вычитания, а также операции сравнения 
 * (для сравнение на больше/меньше считать что левые байты главнее т.е. вначале сравниваются первые байты, 
 * потом вторые и т.д.). Так же реализовать функцию, которая будет определять принадлежность адреса к подсети 
 * по адресу подсети (a1,b1,c1,d1) и битовой маске подсети (a2,b2,c2,d2). Например, адрес 192.168.1.30 принадлежит 
 * подсети 192.168.0.0 с маской 255.255.0.0.
 * Операции сложения, вычитания и сравнения необходимо реализовать в виде перегрузки операторов.
 * Необходимо реализовать пользовательский литерал для работы с константами типа IPAddress.
*/

#include <iostream>

typedef unsigned char uc;

using namespace std;

class IPAddress {
public:
    // конструктор по умолчанию
    IPAddress() {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
    } 
    // параметризированный конструктор
    IPAddress(const int& a, const int& b, const int& c, const int& d) {
        if (a > 255 || a < 0 || b > 255 || b < 0 || c < 0 || c > 255 || d < 0 || d > 255) {
            throw out_of_range("Invalid values (" + to_string(a) + "." + to_string(b) + "." + to_string(c) + "." + to_string(d) + ")");
        }
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
    // getters
    uc GetA() const{
        return a;
    }
    uc& GetA() {
        return a;
    }
    uc GetB() const{
        return b;
    }
    uc& GetB() {
        return b;
    }
    uc GetC() const{
        return c;
    }
    uc& GetC() {
        return c;
    }
    uc GetD() const{
        return d;
    }
    uc& GetD() {
        return d;
    }

private:
    // байты ip адреса
    uc a;
    uc b;
    uc c;
    uc d;
};


// операторы сравнения
bool operator==(const IPAddress& lhs, const IPAddress& rhs) {
    return lhs.GetA() == rhs.GetA() && lhs.GetB() == rhs.GetB() && lhs.GetC() == rhs.GetC() && lhs.GetD() == rhs.GetD();
}

bool operator!=(const IPAddress& lhs, const IPAddress& rhs) {
    return !(lhs.GetA() == rhs.GetA() && lhs.GetB() == rhs.GetB() && lhs.GetC() == rhs.GetC() && lhs.GetD() == rhs.GetD());
}

bool operator<(const IPAddress& lhs, const IPAddress& rhs) {
    if (lhs.GetA() != rhs.GetA()) {
        return lhs.GetA() < rhs.GetA();
    }
    if (lhs.GetB() != rhs.GetB()) {
        return lhs.GetB() < rhs.GetB();
    }
    if (lhs.GetC() != rhs.GetC()) {
        return lhs.GetC() < rhs.GetC();
    }
    return lhs.GetD() < rhs.GetD();
}

bool operator>(const A& lhs, const IPAddress& rhs) {
    if (lhs.GetA() != rhs.GetA()) {
        return lhs.GetA() > rhs.GetA();
    }
    if (lhs.GetB() != rhs.GetB()) {
        return lhs.GetB() > rhs.GetB();
    }
    if (lhs.GetC() != rhs.GetC()) {
        return lhs.GetC() > rhs.GetC();
    }
    return lhs.GetD() > rhs.GetD();
}

// оператор сложения
IPAddress operator+(const IPAddress& lhs, const IPAddress& rhs) {
    uc a = lhs.GetA() + rhs.GetA() > 255 ? 255 : lhs.GetA() + rhs.GetA();
    uc b = lhs.GetB() + rhs.GetB() > 255 ? 255 : lhs.GetB() + rhs.GetB();
    uc c = lhs.GetC() + rhs.GetC() > 255 ? 255 : lhs.GetC() + rhs.GetC();
    uc d = lhs.GetD() + rhs.GetD() > 255 ? 255 : lhs.GetD() + rhs.GetD();
    return {a, b, c, d};
}

// оператор вычитания
IPAddress operator-(const IPAddress& lhs, const IPAddress& rhs) {
    uc a = lhs.GetA() - rhs.GetA() < 0 ? 0 : lhs.GetA() - rhs.GetA();
    uc b = lhs.GetB() - rhs.GetB() < 0 ? 0 : lhs.GetB() - rhs.GetB();
    uc c = lhs.GetC() - rhs.GetC() < 0 ? 0 : lhs.GetC() - rhs.GetC();
    uc d = lhs.GetD() - rhs.GetD() < 0 ? 0 : lhs.GetD() - rhs.GetD();
    return {a, b, c, d};
}

// оператор конъюнкции
IPAddress operator&(const IPAddress& lhs, const IPAddress& rhs) {
    uc a = lhs.GetA() & rhs.GetA();
    uc b = lhs.GetB() & rhs.GetB();
    uc c = lhs.GetC() & rhs.GetC();
    uc d = lhs.GetD() & rhs.GetD();
    return {a, b, c, d};
}

// функция, проверяющая принадлежность адреса к подсети по адресу подсети и маски
bool CheckIp(const IPAddress& ip, const IPAddress& sub, const IPAddress& mask) {
    return (ip & mask) == sub;
}

// оператор ввода 
istream& operator>>(istream& stream, IPAddress& ip) {
    int a, b, c, d;
    stream >> a;
    stream.ignore(1);
    stream >> b;
    stream.ignore(1);
    stream >> c;
    stream.ignore(1);
    stream >> d;
    stream.ignore(1);
    ip = {a, b, c, d};
    return stream;
}

// оператор вывода
ostream& operator<<(ostream& stream, const IPAddress& ip) {
    stream << (int) ip.GetA() << '.' << (int) ip.GetB() << '.' << (int) ip.GetC() << '.' << (int) ip.GetD();
    return stream;
}

// строковый литерал для класса IPAddress
const IPAddress operator"" _ip(const char *str, size_t size) {
    int val = 0;
    int a[4] = {0, 0, 0, 0};
    int k = 0;
    for (int i = 0; i < size; ++i) {
        if (str[i] == '.') {
            a[k++] = val;
            val = 0;
            continue;
        }
        val = 10 * val + str[i] - '0';
    }
    a[3] = val;
    return {a[0], a[1], a[2], a[3]};
}

int main() {
    try {
        IPAddress sub = "192.168.0.0"_ip, mask = "255.255.0.0"_ip, a, b;
        cin >> a >> b;
        cout << "Operator+ : " << a << " + " << b << " = " << a + b << endl;
        cout << "Operator- : " << a << " - " << b << " = " << a - b << endl;
        cout << "Operator< : ";
        if (a < b) {
            cout << a << " < " << b << " (меньше)" << endl;
        }
        else {
            cout << a << " >= " << b << " (не меньше)" << endl;
        }
        cout << "Operator> : ";
        if (a > b) {
            cout << a << " > " << b << " (больше)" << endl;
        }
        else {
            cout << a << " >= " << b << " (не больше)" << endl;
        }
        cout << "Operator== : ";
        if (a == b) {
            cout << a << " = " << b << endl;
        }
        else {
            cout << a << " != " << b << endl;
        }
        cout << "CheckIP(a): ";
        if (CheckIp(a, sub, mask)) {
            cout << a << " belongs to the subnet" << endl;
        }
        else {
            cout << a << " doesn't belong to the subnet" << endl;
        }
    } catch(exception& ex) {
        cout << ex.what() << endl;
    }


    return 0;
}