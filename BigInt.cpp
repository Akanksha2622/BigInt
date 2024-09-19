#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class BigInt {
    string digits;

public:
    // Constructors:
    BigInt(unsigned long long n = 0);
    BigInt(const string &);
    BigInt(const char *);
    BigInt(const BigInt &);

    // Helper Functions:
    friend void divideBy2(BigInt &a);
    friend bool isNull(const BigInt &);
    friend int getLength(const BigInt &);
    int operator[](const int) const;

    // Operator Overloading:

    // Direct assignment
    BigInt &operator=(const BigInt &);

    // Post/Pre - Incrementation
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);

    // Addition and Subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);

    // Comparison operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    // Multiplication and Division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    // Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);

    // Power Function
    friend BigInt &operator^=(BigInt &, const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);

    // Square Root Function
    friend BigInt sqrt(BigInt &a);

    // Read and Write
    friend ostream &operator<<(ostream &, const BigInt &);
    friend istream &operator>>(istream &, BigInt &);

    // Others
    friend BigInt nthCatalan(int n);
    friend BigInt nthFibonacci(int n);
    friend BigInt factorial(int n);
};

// Constructor from string
BigInt::BigInt(const string &s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i])) {
            throw("ERROR: Invalid number");
        }
        digits.push_back(s[i] - '0');
    }
}

// Constructor from unsigned long long
BigInt::BigInt(unsigned long long nr) {
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}

// Constructor from char array
BigInt::BigInt(const char *s) {
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (!isdigit(s[i])) {
            throw("ERROR: Invalid number");
        }
        digits.push_back(s[i] - '0');
    }
}

// Copy constructor
BigInt::BigInt(const BigInt &a) {
    digits = a.digits;
}

// Check if BigInt is zero
bool isNull(const BigInt &a) {
    return a.digits.size() == 1 && a.digits[0] == 0;
}

// Get length of BigInt
int getLength(const BigInt &a) {
    return a.digits.size();
}

// Get digit at index
int BigInt::operator[](const int index) const {
    if (digits.size() <= index || index < 0) {
        throw("ERROR: Index out of bounds");
    }
    return digits[index];
}

// Equality operator
bool operator==(const BigInt &a, const BigInt &b) {
    return a.digits == b.digits;
}

// Inequality operator
bool operator!=(const BigInt &a, const BigInt &b) {
    return !(a == b);
}

// Less than operator
bool operator<(const BigInt &a, const BigInt &b) {
    int n = getLength(a), m = getLength(b);
    if (n != m) {
        return n < m;
    }
    while (n--) {
        if (a.digits[n] != b.digits[n]) {
            return a.digits[n] < b.digits[n];
        }
    }
    return false;
}

// Greater than operator
bool operator>(const BigInt &a, const BigInt &b) {
    return b < a;
}

// Greater than or equal operator
bool operator>=(const BigInt &a, const BigInt &b) {
    return !(a < b);
}

// Less than or equal operator
bool operator<=(const BigInt &a, const BigInt &b) {
    return !(a > b);
}

// Assignment operator
BigInt &BigInt::operator=(const BigInt &a) {
    digits = a.digits;
    return *this;
}

// Pre-increment operator
BigInt &BigInt::operator++() {
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++) {
        digits[i] = 0;
    }
    if (i == n) {
        digits.push_back(1);
    } else {
        digits[i]++;
    }
    return *this;
}

// Post-increment operator
BigInt BigInt::operator++(int temp) {
    BigInt aux = *this;
    ++(*this);
    return aux;
}

// Pre-decrement operator
BigInt &BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1) {
        throw("UNDERFLOW");
    }
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++) {
        digits[i] = 9;
    }
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0) {
        digits.pop_back();
    }
    return *this;
}

// Post-decrement operator
BigInt BigInt::operator--(int temp) {
    BigInt aux = *this;
    --(*this);
    return aux;
}

// Addition assignment operator
BigInt &operator+=(BigInt &a, const BigInt &b) {
    int t = 0, s, i;
    int n = getLength(a), m = getLength(b);
    if (m > n) {
        a.digits.append(m - n, 0);
    }
    n = getLength(a);
    for (i = 0; i < n; i++) {
        if (i < m) {
            s = (a.digits[i] + b.digits[i]) + t;
        } else {
            s = a.digits[i] + t;
        }
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t) {
        a.digits.push_back(t);
    }
    return a;
}

// Addition operator
BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

// Subtraction assignment operator
BigInt &operator-=(BigInt &a, const BigInt &b) {
    if (a < b) {
        throw("UNDERFLOW");
    }
    int n = getLength(a), m = getLength(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m) {
            s = a.digits[i] - b.digits[i] + t;
        } else {
            s = a.digits[i] + t;
        }
        if (s < 0) {
            s += 10;
            t = -1;
        } else {
            t = 0;
        }
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0) {
        a.digits.pop_back();
        n--;
    }
    return a;
}

// Subtraction operator
BigInt operator-(const BigInt &a, const BigInt &b) {
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

// Multiplication assignment operator
BigInt &operator*=(BigInt &a, const BigInt &b) {
    if (isNull(a) || isNull(b)) {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v[i + j] += (a.digits[i] * b.digits[j]);
        }
    }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++) {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--) {
        a.digits.pop_back();
    }
    return a;
}

// Multiplication operator
BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp *= b;
    return temp;
}

// Division assignment operator
BigInt &operator/=(BigInt &a, const BigInt &b) {
    if (isNull(b)) {
        throw("Arithmetic Error: Division By 0");
    }
    if (a < b) {
        a = BigInt();
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, n = getLength(a), m = getLength(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cat[i] = 0; t >= b; cat[i]++) {
            t -= b;
        }
    }
    a.digits.resize(cat.size());
    for (i = 0; i < cat.size(); i++) {
        a.digits[i] = cat[i];
    }
    while (a.digits.size() > 1 && !a.digits.back()) {
        a.digits.pop_back();
    }
    return a;
}

// Division operator
BigInt operator/(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp /= b;
    return temp;
}

// Modulo assignment operator
BigInt &operator%=(BigInt &a, const BigInt &b) {
    if (isNull(b)) {
        throw("Arithmetic Error: Division By 0");
    }
    if (a < b) {
        return a;
    }
    if (a == b) {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, n = getLength(a), m = getLength(b);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (t; t >= b; t -= b);
    }
    a = t;
    return a;
}

// Modulo operator
BigInt operator%(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp %= b;
    return temp;
}

// Power assignment operator
BigInt &operator^=(BigInt &a, const BigInt &b) {
    BigInt Exponent, Base(a);
    a = 1;
    for (int i = 0; i < b.digits.size(); i++) {
        Exponent = Exponent * 10 + b.digits[i];
    }
    while (!isNull(Exponent)) {
        if (Exponent[0] % 2 == 1) {
            a *= Base;
        }
        Base *= Base;
        divideBy2(Exponent);
    }
    return a;
}

// Power operator
BigInt operator^(BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp ^= b;
    return temp;
}

// Divide by 2 function
void divideBy2(BigInt &a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) ? 5 : 0);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back()) {
        a.digits.pop_back();
    }
}

// Square root function
BigInt sqrt(BigInt &a) {
    BigInt left(1), right(a), v(1), mid, prod;
    divideBy2(right);
    while (left <= right) {
        mid += left;
        mid += right;
        divideBy2(mid);
        prod = (mid * mid);
        if (prod <= a) {
            v = mid;
            ++mid;
            left = mid;
        } else {
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}

// Nth Fibonacci number function
BigInt nthFibonacci(int n) {
    BigInt a(1), b(1), c;
    if (n == 0) {
        return c;
    }
    n--;
    while (n--) {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}

// Factorial function
BigInt factorial(int n) {
    BigInt f(1);
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

// Output stream operator
ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        out << (short)a.digits[i];
    }
    return out;
}

// Input stream operator
istream &operator>>(istream &in, BigInt &a) {
    string s;
    in >> s;
    a = BigInt(s);
    return in;
}

// Main function
int main() {
    BigInt num1, num2;

    cout << "Enter the first big integer: ";
    cin >> num1;
    cout << "Enter the second big integer: ";
    cin >> num2;

    cout << "Addition: " << num1 + num2 << endl;
    cout << "Subtraction: " << num1 - num2 << endl;
    cout << "Multiplication: " << num1 * num2 << endl;
    cout << "Division: " << num1 / num2 << endl;
    cout << "Modulo: " << num1 % num2 << endl;

    return 0;
}
