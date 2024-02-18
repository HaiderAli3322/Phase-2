//
// Created by ompat on 2024-02-18.
//

#ifndef TRANSACTION_CLASS_TRANSACTION_H
#define TRANSACTION_CLASS_TRANSACTION_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Transaction{
protected:
    string transactionCode;
public:
    bool parse();
};

#endif //TRANSACTION_CLASS_TRANSACTION_H
