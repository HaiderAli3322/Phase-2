// TransactionProcessor.cpp
#include "header.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

TransactionProcessor::TransactionProcessor(FileManager& fm, Session& session)
    : fileManager(fm), currentSession(session), isLoggedIn(false) {}

bool TransactionProcessor::isUserLoggedIn() const {
    return isLoggedIn;
}

void TransactionProcessor::processTransaction(const std::string& transactionCode) {
    std::string digitCode = transactionCode.substr(0, 2);

    if (digitCode != "01" && digitCode != "00" && !isUserLoggedIn()) {
        std::cout << "Error: User must log in before processing transactions." << std::endl;
        return;
    }

    if (digitCode == "01") processLogin();
    else if (digitCode == "02") processLogout();
    else if (digitCode == "03") processSell();
    else if (digitCode == "04") processBuy();
    else if (digitCode == "05") processRefund();
    else if (digitCode == "06") processAddCredit();
    else if (digitCode == "00") processEndOfSession();
    else std::cout << "Error: Invalid transaction code: " << digitCode << std::endl;
}

bool isAlphanumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isalnum(c); });
}

void TransactionProcessor::processCreate() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before creating a new user account." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() != "admin") {
        std::cout << "Error: Only admin users can create new user accounts." << std::endl;
        return;
    }

    std::string newUsername;
    std::cout << "Enter the new username: ";
    std::getline(std::cin, newUsername);

    if (newUsername.empty() || newUsername.length() > 15 || !isAlphanumeric(newUsername)) {
        std::cout << "Error: Invalid username. It must be alphanumeric, between 1 and 15 characters." << std::endl;
        return;
    }


    if (fileManager.isUserExists(newUsername)) {
        std::cout << "Error: User '" << newUsername << "' already exists." << std::endl;
        return;
    }

    std::string userType;
    std::cout << "Enter the type of user (admin, full-standard, buy-standard, sell-standard): ";
    std::getline(std::cin, userType);

    if (userType != "admin" && userType != "full-standard" && userType != "buy-standard" && userType != "sell-standard") {
        std::cout << "Error: Invalid user type." << std::endl;
        return;
    }

    std::string transactionCode = "01_" + newUsername + "_" + userType;
    fileManager.writeDailyTransactionFile("transactions.txt", transactionCode);

    User newUser = User(newUsername, userType, 0);
    fileManager.updateUsersFile("users.txt", newUsername, userType, 0);


    std::cout << "User account '" << newUsername << "' successfully created." << std::endl;
    logTransaction("Create transaction processed successfully");
}

void TransactionProcessor::processDelete() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before deleting a user account." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() != "admin") {
        std::cout << "Error: Only admin users can delete user accounts." << std::endl;
        return;
    }

    std::string usernameToDelete;
    std::cout << "Enter the username to delete: ";
    std::getline(std::cin, usernameToDelete);

    if (!fileManager.isUserExists(usernameToDelete)) {
        std::cout << "Error: User '" << usernameToDelete << "' does not exist." << std::endl;
        return;
    }

    if (usernameToDelete == currentSession.getCurrentSession()->getUsername()) {
        std::cout << "Error: Cannot delete the current user's account." << std::endl;
        return;
    }

    std::string transactionCode = "02_" + usernameToDelete;
    //TALK TO HAIDER
    fileManager.writeDailyTransactionFile("transaction.txt", transactionCode);

    //TALK TO HAIDER
    fileManager.removeUser(usernameToDelete);
    std::cout << "User account '" << usernameToDelete << "' successfully deleted." << std::endl;
    logTransaction("Delete transaction processed successfully");
}

void TransactionProcessor::processSell() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before selling a game." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() == "buy-standard") {
        std::cout << "Error: buy-standard users cannot sell games." << std::endl;
        return;
    }
    string tempName="";
    
    InputValidator checker;
    std::cout << "Enter the game name (up to 25 characters): ";
    std::getline(std::cin, tempName);
    
    

    double price;
    std::cout << "Enter the price for the game (in dollars, e.g., 15.00): ";
    std::cin >> price;

    if (price <= 0 || price > 999.99) {
        std::cout << "Error: Invalid price. Price must be between 0.01 and 999.99." << std::endl;
        return;
    }

    if(checker.validateGame(tempName) && checker.validatePrice(price) && checker.validateUser(currentSession.getCurrentSession()->getUsername(), currentSession.getCurrentSession()->getUserType())){
        Game game(tempName, currentSession.getCurrentSession()->getUsername(), price);
    

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string transactionCode = "03_" + game.getGameName() + "_" + game.getSellerName() + "_" + std::to_string(game.getGamePrice());
    fileManager.writeDailyTransactionFile("transactions",transactionCode);

    
    fileManager.updateGamesFile("gameFile",game.getGameName(),std::to_string(game.getGamePrice()),game.getSellerName());

    logTransaction("Game successfully listed for sale.");
    }
}

void TransactionProcessor::processBuy() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before making a purchase." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() == "standard-sell") {
        std::cout << "Error: Standard-sell users are not allowed to make purchases." << std::endl;
        return;
    }

    std::string gameName;
    std::cout << "Enter the name of the game you want to purchase: ";
    std::getline(std::cin, gameName);

    if (!fileManager.isGameExists(gameName)) {
        std::cout << "Error: Game '" << gameName << "' does not exist." << std::endl;
        return;
    }

    std::string sellerName;
    std::cout << "Enter the seller's username: ";
    std::getline(std::cin, sellerName);

    if (!fileManager.isUserExists(sellerName)) {
        std::cout << "Error: Seller '" << sellerName << "' does not exist." << std::endl;
        return;
    }
    Game gameBeingSold = Game::getGameByName(gameName);
    double gamePrice = gameBeingSold.getGamePrice();

    if (currentSession.getCurrentSession()->getBalance() < gamePrice) {
        std::cout << "Error: Insufficient funds. You do not have enough money to purchase the game." << std::endl;
        return;
    }


    if (currentSession.getCurrentSession()->ownsGame(gameName)) {
        std::cout << "Error: You already own a copy of the game '" << gameName << "'." << std::endl;
        return;
    }

    User seller = User::getUserByName(sellerName);

    currentSession.getCurrentSession()->withdraw(gamePrice);
    fileManager.updateUsersFile("users.txt", sellerName, seller.getUserType(), gamePrice);
    currentSession.getCurrentSession()->addGame(gameName);

    std::string transactionCode = "04_" + gameName + "_" + sellerName + "_" + currentSession.getCurrentSession()->getUsername() + "_" + std::to_string(gamePrice);
    fileManager.writeDailyTransactionFile("dailyTransaction",transactionCode);

    std::cout << "Purchase successful. You now own the game '" << gameName << "'." << std::endl;
    logTransaction("Buy transaction processed successfully");
}

void TransactionProcessor::processRefund() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before processing a refund." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() != "admin") {
        std::cout << "Error: Only admins are allowed to issue refunds." << std::endl;
        return;
    }

    std::string buyerName;
    std::cout << "Enter the buyer's username: ";
    std::getline(std::cin, buyerName);

    if (!fileManager.isUserExists(buyerName)) {
        std::cout << "Error: Buyer '" << buyerName << "' does not exist." << std::endl;
        return;
    }

    std::string sellerName;
    std::cout << "Enter the seller's username: ";
    std::getline(std::cin, sellerName);

    if (!fileManager.isUserExists(sellerName)) {
        std::cout << "Error: Seller '" << sellerName << "' does not exist." << std::endl;
        return;
    }

    double creditAmount;
    std::cout << "Enter the amount of credit to transfer: $";
    std::cin >> creditAmount;

    if (creditAmount <= 0) {
        std::cout << "Error: Invalid credit amount. Please enter a positive value." << std::endl;
        return;
    }

    fileManager.getUserByUsername(sellerName).deductAmount(creditAmount);
    fileManager.getUserByUsername(buyerName).creditAmount(creditAmount);

    std::string transactionCode = "05_" + buyerName + "_" + sellerName + "_" + std::to_string(creditAmount);
    fileManager.writeDailyTransactionFile(transactionCode);

    std::cout << "Refund successful. $" << creditAmount << " credited from '" << sellerName << "' to '" << buyerName << "'." << std::endl;
    logTransaction("Refund transaction processed successfully");
}

void TransactionProcessor::processAddCredit() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before adding credit." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() != "admin") {
        std::cout << "Error: Only admins are allowed to add credit." << std::endl;
        return;
    }

    std::string username;
    if (currentSession.getCurrentSession()->getUserType() == "admin") {
        std::cout << "Enter the username of the account to which credit is being added: ";
        std::getline(std::cin, username);

        if (!fileManager.isUserExists(username)) {
            std::cout << "Error: User '" << username << "' does not exist." << std::endl;
            return;
        }
    }
    else {
        username = currentSession.getCurrentSession()->getUsername();
    }

    double creditAmount;
    std::cout << "Enter the amount of credit to add: $";
    std::cin >> creditAmount;

    if (creditAmount <= 0 || creditAmount > 1000) {
        std::cout << "Error: Invalid credit amount. Please enter a positive value up to $1000.00." << std::endl;
        return;
    }

    fileManager.getUserByUsername(username).creditAmount(creditAmount);

    std::string transactionCode = "06_" + username + "_$" + std::to_string(creditAmount);
    fileManager.writeDailyTransactionFile("transactions.txt", transactionCode);

    std::cout << "Credit added successfully. $" << creditAmount << " credited to '" << username << "'." << std::endl;
    logTransaction("Add credit transaction processed successfully");
}

void TransactionProcessor::processList() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before listing items." << std::endl;
        return;
    }

    std::vector<Game> gamesFile = fileManager.getAvailableGames();

    std::cout << "List of Available Games:" << std::endl;
    std::cout << "------------------------" << std::endl;

    for (const auto& game : gamesFile) {
        std::cout << "Game Name: " << game.getName() << std::endl;
        std::cout << "Seller: " << game.getSellerName() << std::endl;
        std::cout << "Price: $" << game.getPrice() << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    logTransaction("List transaction processed successfully");
}

void TransactionProcessor::processUserList() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before viewing the user list." << std::endl;
        return;
    }

    if (currentSession.getCurrentSession()->getUserType() != "admin") {
        std::cout << "Error: User must be an admin to view the user list." << std::endl;
        return;
    }

    std::vector<User> usersFile = fileManager.getActiveUsers();

    std::cout << "List of Active Users:" << std::endl;
    std::cout << "---------------------" << std::endl;

    //TO:DO fix lol
    for (const auto& user : usersFile) {
        std::cout << "Username: " << user.getUsername() << std::endl;
        std::cout << "Account Type: " << user.getUserType() << std::endl;
        std::cout << "Credit: $" << user.getBalance() << std::endl;
        std::cout << "---------------------" << std::endl;
    }

    logTransaction("User List transaction processed successfully");
}

void TransactionProcessor::processEndOfSession() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before ending the session." << std::endl;
        return;
    }

    std::vector<std::string> sessionTransactions = fileManager.getSessionTransactions();
    fileManager.writeDailyTransactionFile("transactions.txt", sessionTransactions);

    std::cout << "End of session. Daily transactions logged." << std::endl;

    currentSession.endSession(currentSession.getCurrentSession());
    logTransaction("End of Session transaction processed successfully");
}

void TransactionProcessor::processLogin() {
    if (isUserLoggedIn()) {
        std::cout << "Error: User '" << currentSession.getCurrentSession()->getUsername() << "' is already logged in." << std::endl;
        return;
    }

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    if (!fileManager.isUserExists(username)) {
        std::cout << "Error: User '" << username << "' does not exist." << std::endl;
        return;
    }

    std::string userType = fileManager.getUserTypeByUsername(username);

    if (userType == "admin" || userType == "full-standard" || userType == "buy-standard" || userType == "sell-standard") {
        isLoggedIn = true;
        currentSession.startSession(fileManager.getUserByUsername(username));
        std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
        logTransaction("Login transaction processed successfully");
    }
    else {
        std::cout << "Error: Invalid user type for login." << std::endl;
    }
}

void TransactionProcessor::processLogout() {
    if (!isUserLoggedIn()) {
        std::cout << "Error: No user is currently logged in." << std::endl;
        return;
    }

    std::cout << "Logout successful. Goodbye, " << currentSession.getCurrentSession()->getUsername() << "!" << std::endl;
    currentSession.endSession(currentSession.getCurrentSession());
    logTransaction("Logout transaction processed successfully");
}

void TransactionProcessor::writeDailyTransactionFile(const std::vector<std::string>& transactions) {
    std::ofstream dailyTransactionFile(fileManager.getDailyTransactionFilePath(), std::ios_base::app);

    if (dailyTransactionFile.is_open()) {
        for (const auto& transaction : transactions) {
            dailyTransactionFile << transaction << std::endl;
        }
        dailyTransactionFile.close();
    }
    else {
        std::cerr << "Error: Unable to open daily transaction file for writing." << std::endl;
    }
}

void TransactionProcessor::logTransaction(const std::string& logMessage) const {
    std::ofstream logFile(fileManager.getLogFilePath(), std::ios_base::app);

    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Error: Unable to open log file for writing." << std::endl;
    }
}
