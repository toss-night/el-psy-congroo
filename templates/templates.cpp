#include <iostream>
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


int main()
{
    
  
}

