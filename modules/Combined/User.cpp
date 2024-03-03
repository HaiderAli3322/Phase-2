//
// Created by harish on 2/16/2024.
//

#include "header.h"
#include "vector"
#include "sstream"

//Constructor
User::User(string username, string userType, double balance) {
    this->username = username;
    this->userType = userType;
    this->balance = balance;
}

//Default Constructor
User::User() {
    this->username = "";
    this->userType = "";
    this->balance = 0;
}

//Get username
string User::getUsername() {
    return this->username;
}

//Get userType
string User::getUserType() {
    return this->userType;
}

//Get balance
double User::getBalance() {
    return this->balance;
}

//Set balance
void User::setBalance(double balance) {
    this->balance = balance;
}

//Set username
void User::setUsername(string username) {
    this->username = username;
}

//Set userType
void User::setUserType(string userType) {
    this->userType = userType;
}

//Deposit money to balance
void User::deposit(double amount) {
    this->balance += amount;
}


//Withdraw money from balance
void User::withdraw(double amount) {
    this->balance -= amount;
}

bool User::ownsGame(const string &name) {
    return ownedGames.find(name) != ownedGames.end();
}

void User::addGame(const std::string &name) {
    ownedGames.insert(name);
}

void User::removeGame(const std::string &name) {
    ownedGames.erase(name);
}

User getUserByName(string name) {
    ifstream inFile("users.txt");
    string line;

    if(inFile.is_open()) {
        while(getline(inFile, line)) {

            vector<string> tokens;
            stringstream check1(line);
            string intermediate;

            while(getline(check1, intermediate, ',')) {
                tokens.push_back(intermediate);
            }

            if(tokens[0] == name) {
                return User(tokens[0], tokens[1], stod(tokens[2]));
            }


        }
    }
}

