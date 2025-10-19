#include <iostream>
#include <cmath>
using namespace std;

int fsum(int a, int b, bool c)
{
    if (c)
    {
        return a + b;
    }
    else
        return a - b;
}

int fmul(int a, int b)
{
    return a * b;
}

float fdiv(float a, float b)
{
    if (b == 0)
    {
        cout << "Ошибка, на 0 делить нельзя!" << endl;
        return INFINITY;
    }
    return a / b;
}

float fsqr(float a)
{
    return sqrt(a);
}

int fpow(int a, int b)
{
    return pow(a, b);
}



int main()
{
    setlocale(LC_ALL, "ru");

    int a, b;
    char c;
    cout << "Калькулятор. Знаки: (+,-,*,/,#,^)" << endl << "Введите первое число: ";
    cin >> a;
    cout << "Введите знак: ";
    cin >> c;

    if (c == '#')
    {
        cout << fsqr(a) << endl;
        return 0;
    }

    cout << "Введите второе число: ";
    cin >> b;
    cout << endl;

    cout << "Ответ: ";
    switch (c)
    {
    case '+':
        cout << fsum(a, b, 1) << endl;
        break;

    case '-':
        cout << fsum(a, b, 0) << endl;
        break;

    case '*':
        cout << fmul(a, b) << endl;
        break;

    case '/':
        cout << fdiv(a, b) << endl;
        break;

    case '^':
        cout << fpow(a, b) << endl;
        break;

    default:
        cout << "Неизвестная операция!" << endl;
        return 0;
    }


}