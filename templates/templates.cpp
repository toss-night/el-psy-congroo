#include <iostream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

template<typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

template<typename T1,typename T2>
class Pair
{
public:
    T1 first;
    T2 second;
    Pair(T1 f, T2 s) :first(f), second(s) {}

    T1 getFirst() { return first; }
    T2 getSecond() { return second; }

    void setFirst(T1 a) { first = a; }
    void setSecond(T2 a) { second = a; }

    void swap()
    {
        Pair<T2, T1> par(second, first);
        second = par.getFirst();
        first = par.getSecond();
    }
    void print()
    {
        cout << first << "\t" << second << endl;
    }
};

template<typename T3, size_t siz>
void printArray(T3(&arr)[siz])
{
    for (size_t i = 0; i < siz; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printAll() 
{
    cout << endl;
}
template<typename T4, typename... T5>
void printAll(T4 first, T5...second)
{
    cout << first;
    if constexpr (sizeof...(second) > 0)
    {
        cout << ", ";
        printAll(second...);
    }
}

template<typename T1, typename T2, typename T3>
class Tuple
{
    public:
        T1 first;
        T2 second;
        T3 third;

        Tuple(T1 t1, T2 t2, T3 t3) : first(t1), second(t2), third(t3) {}

        T1 getFirst() { return first; }
        T2 getSecond() { return second; }
        T3 getThird() { return third; }

        void print()
        {
            cout << first << " " << second << " " << third << endl;
        }

};


template<typename T1>
T1 sumAll(T1 first)
{
    return first;
}

template<typename T1, typename...T2>
auto sumAll(T1 first, T2... other)
{
    return first + sumAll(other...);
}

template<typename T>
class Storage
{
public:
    void store(vector<T>vec) {}
};
template<>
class Storage<bool>
{
public:
    void store(bool bol) {}
};
template<>
class Storage<const char*>
{
public:
    void store(const char* chr) {}
};

template<typename T>
string getTypeName() { return "unknown"; }
template<>
string getTypeName<int>() { return "int"; }
template<>
string getTypeName<double>() { return "double"; }
template<>
string getTypeName<bool>() { return "bool"; }
template<>
string getTypeName<string>() { return "string"; }

template<typename T>
class Calculator
{
public:
    T add(T a, T b) { return a + b; }
};
template<>
class Calculator<string>
{
public:
    string add(string a, string b)
    {
        for (char c : b)
        {
            a.push_back(c);
        }
        return a;
    }
};

template<int N>
struct Factorial
{
    static const int value = N * Factorial<N - 1>::value;
};
template<>
struct Factorial<0>
{
    static const int value = 1;
};

template<typename T>
struct IsPointer
{
    static const bool value = false;
};
template<typename T>
struct IsPointer<T*>
{
    static const bool value = true;
};

template<typename T, typename U>
struct IsSame
{
    static const bool value = false;
};
template<typename T>
struct IsSame<T, T>
{
    static const bool value = true;
};

template<typename T>
struct IsArithmetic
{
    static const bool value = false;
};
template<>
struct IsArithmetic<int> { static const bool value = true; };
template<>
struct IsArithmetic<bool> { static const bool value = true; };
template<>
struct IsArithmetic<double> { static const bool value = true; };
template<>
struct IsArithmetic<float> { static const bool value = true; };
template<>
struct IsArithmetic<short> { static const bool value = true; };
template<>
struct IsArithmetic<long> { static const bool value = true; };
template<>
struct IsArithmetic<long long> { static const bool value = true; };
template<>
struct IsArithmetic<long double> { static const bool value = true; };
template<>
struct IsArithmetic<char> { static const bool value = true; };


   
int main()
{
    cout << Factorial<5>::value << endl;
    static_assert(Factorial<5>::value == 120, "error");
}

