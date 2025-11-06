#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

void swapValues(int* a, int* b) 
{
    int c = *a;
    *a = *b;
    *b = c;
}

void swapValuesRef(int& a, int& b) 
{
    int c = a;
    a = b;
    b = c;
}

class Point 
{
public:
    int x, y;
    Point() {}
    Point(int a, int b) :x(a), y(b) {}
};


Point* createPoint(int x, int y) 
{
    Point *z = new Point(x, y);
    return z;
}

void doubleArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(arr+i) *= 2;
    }
}






int main()
{
    setlocale(LC_ALL, "ru");

    
}

