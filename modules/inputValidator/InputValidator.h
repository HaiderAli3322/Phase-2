#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
using namespace std;

class InputValidator {
public:
    bool isStringInRange(string& u);
    bool validateUser(string& u, string& uType);
    bool validateGame(string& g);
    bool validatePrice(double p);
};

#endif