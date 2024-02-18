#include "InputValidator.h"
#include <iostream>

using namespace std;
bool InputValidator::isStringInRange(string& u) {
    for (char ch : u) {
        int ascii = static_cast<int>(ch);
        if (ascii < 65 || ascii > 122) {
            return false;
        }
    }
    return true;
}

bool InputValidator::validateUser(string& u, string& uType) {
    if (u.length() <= 15) {
        if (uType.length() <= 2) {
            if (!isStringInRange(u)) {
                cout << "There are special characters in the name!" << endl;
                return false;
            }
            if (uType != "AA" && uType != "FS" && uType != "BS" && uType != "SS") {
                cout << "The user type is incorrect" << endl;
                return false;
            }
        } else {
            cout << "User Type is too long!" << endl;
            return false;
        }
    } else {
        cout << "User name is too long!" << endl;
        return false;
    }
    return true;
}

bool InputValidator::validateGame(string& g) {
    if (g.length() <= 19) {
        if (!isStringInRange(g)) {
            cout << "There are special characters in the Game name!" << endl;
            return false;
        }
    } else {
        cout << "Game name is too long!" << endl;
        return false;
    }
    return true;
}

bool InputValidator::validatePrice(double p) {
    if (p >= 10 && p < 10000) {
        return true;
    }
    std::cout << "Invalid price! Please keep the price between ($10 - $9,999)" << std::endl;
    return false;
}