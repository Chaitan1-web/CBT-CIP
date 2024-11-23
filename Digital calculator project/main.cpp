#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void show_Menu();
bool isValidNumber(const string &input);
template <typename T>
T get_Validated_Input();
void add_Numbers();
void subtract_Numbers();
void multiply_Numbers();
void divide_Numbers();
void power_Operation();

int main() {
    char choice;
    do {
        show_Menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                add_Numbers();
                break;
            case '2':
                subtract_Numbers();
                break;
            case '3':
                multiply_Numbers();
                break;
            case '4':
                divide_Numbers();
                break;
            case '5':
                power_Operation();
                break;
            case '6':
                cout << "Exiting the calculator. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    } while (choice != '6');

    return 0;
}

// Function to display the menu
void show_Menu() {
    cout << "========== Digital Calculator ==========" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Power Operation" << endl;
    cout << "6. Exit" << endl;
    cout << "========================================" << endl;
}

// Function to validate if a string is a valid number
bool isValidNumber(const string &input) {
    try {
        stod(input); 
        return true;
    } catch (...) {
        return false;
    }
}

// Function to get validated numerical input
template <typename T>
T get_Validated_Input() {
    string input;
    T value;
    while (true) {
        cout << "Enter a number: ";
        cin >> input;

        if (isValidNumber(input)) {
            try {
                value = static_cast<T>(stod(input));
                break;
            } catch (...) {
                cout << "Number too large or invalid for the data type. Try again." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a valid number." << endl;
        }
    }
    return value;
}

// Function for addition
void add_Numbers() {
    cout << "=== Addition ===" << endl;
    double num1 = get_Validated_Input<double>();
    double num2 = get_Validated_Input<double>();
    cout << "Result: " << (num1 + num2) << endl;
}

// Function for subtraction
void subtract_Numbers() {
    cout << "=== Subtraction ===" << endl;
    double num1 = get_Validated_Input<double>();
    double num2 = get_Validated_Input<double>();
    cout << "Result: " << (num1 - num2) << endl;
}

// Function for multiplication
void multiply_Numbers() {
    cout << "=== Multiplication ===" << endl;
    double num1 = get_Validated_Input<double>();
    double num2 = get_Validated_Input<double>();
    cout << "Result: " << (num1 * num2) << endl;
}

// Function for division
void divide_Numbers() {
    cout << "=== Division ===" << endl;
    double num1 = get_Validated_Input<double>();
    double num2;
    while (true) {
        num2 = get_Validated_Input<double>();
        if (num2 == 0) {
            cout << "Cannot divide by zero. Enter a different number." << endl;
        } else {
            break;
        }
    }
    cout << "Result: " << (num1 / num2) << endl;
}

// Function for power operation
void power_Operation() {
    cout << "=== Power Operation ===" << endl;
    double base = get_Validated_Input<double>();
    int exponent = get_Validated_Input<int>();
    cout << "Result: " << pow(base, exponent)<<endl;
}
