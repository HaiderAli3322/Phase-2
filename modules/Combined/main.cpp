//
// Created by haris on 3/3/2024.
//

#include "header.h"

using namespace std;




int main() {
    TransactionProcessor tp;
    cout << "Welcome User!" << endl;
    cout << "Select an option from the following: " << endl;
    cout << "1. Login" << endl;
    cout << "2. Logout" << endl;
    cout << "3. Buy" << endl;
    cout << "4. Refund" << endl;
    cout << "5. Add Credit" << endl;
    cout << "6. Exit" << endl;

    int option;
    cin >> option;

    while (option != 6) {
        if (option == 1) {
            tp.processLogin();
        } else if (option == 2) {
            tp.processLogout();
        } else if (option == 3) {
            //tp.processBuy();
        } else if (option == 4) {
            tp.processRefund();
        } else if (option == 5) {
            tp.processAddCredit();
        } else {
            cout << "Invalid option!" << endl;
        }

        cout << "Select an option from the following: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Logout" << endl;
        cout << "3. Buy" << endl;
        cout << "4. Refund" << endl;
        cout << "5. Add Credit" << endl;
        cout << "6. Exit" << endl;

        cin >> option;
    }

    return 0;
}
