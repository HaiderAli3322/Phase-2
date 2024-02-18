#include <iostream>
#include "fileManager.h"
//method called readUserFiler that reads the user file void method type

    void fileManager::readUserFile(){
        ifstream inFile("users.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Unable to open file: users.txt" << endl;
        }

    }
    //method called readGamesFile that reads the games file void method type
    void fileManager::readGamesFile(){
    ifstream inFile("games.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Unable to open file: games.txt" << endl;
        }


    }

    //method called writeTransactionsFile that allows us to update the ransactions file and add new transactions to the file
    void fileManager::writeTransactionFile(const string& filename, const string& transactionCode) {
        ofstream outFile(filename, ios::app); // Open file in append mode
        if (outFile.is_open()) {
            outFile << transactionCode << endl;
            cout << "Transaction details added to file." << endl;
            outFile.close();
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }


    //method called updateUsersFile that allows us to update the users file and add new users to the file
    void fileManager::updateUsersFile(const string& filename, const string& username, const string& userType, const int& balance){
    // want to update the users file with the username, userType and balance
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << username << "_" << userType << "_" << balance << endl;
            cout << "User added to file." << endl;
            outFile.close();
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    //method called updateGamesFile that allows us to update the games file and add new games to the file
    void fileManager::updateGamesFile( const string& filename, const string& gameName, const string&gamePrice, const string& sellerName){

        ofstream outFile("games.txt", ios::app);
        if (outFile.is_open()) {
            outFile << gameName+"_" << gamePrice +"_" << sellerName + "_" << endl;
            cout << "Game added to file." << endl;
            outFile.close();
        } else {
            cout << "Unable to open file: games.txt" << endl;
        }

    }

    //method called readTransactionsFile that reads the transactions file void method type
    void fileManager::readTransactionsFile(){
        ifstream inFile("transactions.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Unable to open file: transactions.txt" << endl;
        }

    }










/*
int main() {
    fileManager fileManager;
    fileManager.writeTransactionFile("transactions.txt", "03_iiiiiiiiiiiiiiiiiii_ssssssssssssss_pppppp");
    fileManager.updateUsersFile("users.txt", "african", "Admin", 100);
    fileManager.updateGamesFile("games.txt", "FIFA 22", "100", "african");
    fileManager.readUserFile();
    fileManager.readGamesFile();
    fileManager.readTransactionsFile();
    return 0;
}
*/