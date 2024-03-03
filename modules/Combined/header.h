

#ifndef FILEMANGER_FILEMANAGER_H
#define FILEMANGER_FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "vector"
#include "Game.cpp"

using namespace std;
//---------------------------------------------
class User {
private:
    string username;
    string userType;
    double balance;
    set<std::string> ownedGames;

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
    bool ownsGame(const std::string& name);
    void addGame(const std::string& name);
    void removeGame(const std::string& name);
    static User getUserByName(string name);
};
//---------------------------------------------

class Game {
private:

    string gameName="";
    string userName="";
    double price=0;

public:
    Game(const std::string& g, const std::string& u, double p);
    void setGameName(string g);
    void setSellerName(string u);
    void setPrice(double p);
    string getGameName();
    string getSellerName();
    double getGamePrice();
    static Game getGameByName(string name);

};
//---------------------------------------------
class FileManager{
protected:
    string userFile;
    string gamesFile;
    string transactionsFile;
public:
    void readUserFile();
    void readGamesFile();
    bool isGameExists(string name);
    void writeDailyTransactionFile(const string& filename, const string& transactionCode);
    void updateUsersFile(const string& filename, const string& username, const string& userType, const int& balance);
    void updateGamesFile(const string& filename, const string& gamePrice, const string& gameName, const string& sellerName);
    void readTransactionsFile();
    void removeUser(const string& username);
    bool isUserExists(string username);
    vector<Game> getAvailableGames();
    vector<User>getUsers();


};

//---------------------------------------------
//---------------------------------------------
class InputValidator {
public:
    bool isStringInRange(const string& u);
    bool validateUser(const string& u,const string& uType);
    bool validateGame(const string& g);
    bool validatePrice(double p);
};
//---------------------------------------------
class Session {
private:
    User* currentSession;

public:
    Session(User* currentSession);
    Session();
    User* getSession();
    User* setSession(User* currentSession);
    void startSession(User* currentSession);
    void endSession(User* currentSession);
    User* getCurrentSession() const;
};
//---------------------------------------------
class Transaction{
protected:
    string transactionCode;
public:
    bool parse();
};
//---------------------------------------------



class TransactionProcessor {
private:
    FileManager& fileManager;  // Reference to FileManager object
    Session& currentSession;   // Reference to Session object
    std::vector<std::string> sessionTransactions= {};
    // Private helper method to check if a user is logged in
    bool isLoggedIn;

public:
    // Constructor with references to FileManager and Session objects
    TransactionProcessor(FileManager& fm, Session& session);
    TransactionProcessor();

    // Method to process a transaction
    void processTransaction(const std::string& transactionCode);
    bool isUserLoggedIn() const;

    //helper methods for each transaction type
    void processLogin();
    void processLogout();
    void processCreate();
    void processDelete();
    void processSell();
    void processBuy();
    void processRefund();
    void processAddCredit();
    void processList();
    void processUserList();
    void processEndOfSession();
private:
    void appendTransaction(const std::string& transactionDetails);
    std::vector<std::string>& getSessionTransactions();
    // Private helper method to log transaction details
    void logTransaction(const std::string& transactionDetails);
};


#endif 
