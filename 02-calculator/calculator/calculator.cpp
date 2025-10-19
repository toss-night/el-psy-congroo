#include <iostream>
using namespace std;

int main() 
{
    double a, b;
    char op;

    cout << "=== КАЛЬКУЛЯТОР ===" << endl;

    cout << "Введите первое число: ";

    cin >> a;

    cout << "Введите операцию (+, -, *, /): ";

    cin >> op;

    cout << "Введите второе число: ";

    cin >> b;

    switch (op) 
    {
    case '+': 
        cout << "Результат: " << a + b << endl; break;

    case '-': 
        cout << "Результат: " << a - b << endl; break;

    case '*': 
        cout << "Результат: " << a * b << endl; break;

    case '/':

        if (b != 0) 
        {
            cout << "Результат: " << a / b << endl;
        }       
        else 
        {
            cout << "Ошибка: деление на ноль!" << endl;
        }
        break;

    default: 
        cout << "Неизвестная операция!" << endl;
    }

    return 0;
}