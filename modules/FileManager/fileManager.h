//
// Created by ompat on 2024-02-18.
//

#ifndef FILEMANGER_FILEMANAGER_H
#define FILEMANGER_FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class fileManager{
protected:
    string userFile;
    string gamesFile;
    string transactionsFile;
public:
    void readUserFile();
    void readGamesFile();
    void writeTransactionFile(const string& filename, const string& transactionCode);
    void updateUsersFile(const string& filename, const string& username, const string& userType, const int& balance);
    void updateGamesFile(const string& filename, const string& gamePrice, const string& gameName, const string& sellerName);
    void readTransactionsFile();

};

#endif //FILEMANGER_FILEMANAGER_H
