#include "menu.h"

int main() {

    while (true) {

        string input;
        cout << "\nEnter the number of task(1-6):" << endl;
        getline(cin, input);

        if (input == "1") {
            task1();
        } else if (input == "2") {
            cout << "Enter the command for set(SETADD, SETDEL, SETAT, SETPRINT):" << endl;
            task2();
        } else if (input == "3") {
            task3();
        } else if (input == "4") {
            task4();
        } else if (input == "5") {
            task5();
        } else if (input == "6") {
            task6();
        } else if (input == "EXIT") {
            break;
        } else {
            cerr << "Invalid number of task" << endl;
        }
    }

    return 0;

}
