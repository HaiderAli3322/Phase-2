//
// Created by harish on 2/16/2024.
//
#ifndef SQAPROJECT_USER_H
#define SQAPROJECT_USER_H

#include <string>

using namespace std;


class User {
private:
    string username;
    string userType;
    double balance;

public:
    User(string username, string userType, double balance);
    User();
    string getUsername();
    string getUserType();
    double getBalance();
    void setBalance(double balance);
    void setUsername(string username);
    void setUserType(string userType);
    void deposit(double amount);
    void withdraw(double amount);
};


#endif //SQAPROJECT_USER_H
