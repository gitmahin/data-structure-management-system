#include <iostream>
#include <string>

using namespace std;

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int division(int a, int b) { return a / b; }

int multiply(int a, int b) { return a * b; }

int main()
{
    char option;
    int a, b, result;

    cout << "Options:" << endl;
    cout << "a -> add" << endl;
    cout << "b -> subtract" << endl;
    cout << "c -> division" << endl;
    cout << "d -> multiply" << endl;

    cout << "Choose an option: ";
    cin >> option;

    cin.ignore();

    cout << "Enter number a: ";
    cin >> a;
    cout << "Enter number b: ";
    cin >> b;

    switch (option)
    {
        case 'a':
            result = add(a, b);
            break;
        case 'b':
            result = subtract(a, b);
            break;
        case 'c':
            result = division(a, b);
            break;
        case 'd':
            result = multiply(a, b);
            break;
        default:
            break;
    }

    cout<<"Your result is: "<<result<<endl;
}