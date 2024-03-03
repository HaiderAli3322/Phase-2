// TransactionProcessor.cpp
#include "../transactionprocessor/TransactionProcessor.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <limits>
#include "../session/Session.h"
#include "../user/User.h"
#include "../game/Game.h"
#include <algorithm>  // for std::all_of
#include <vector>
#include "../filemanager/FileManager.h"


//initializes transactionprocessor and instances of filemanager and session, and initial login state
TransactionProcessor::TransactionProcessor(FileManager& fm, Session& session)
        : fileManager(fm), currentSession(session), isLoggedIn(false) {}

bool TransactionProcessor::isUserLoggedIn() const {//checks if user is logged in
    return isLoggedIn;
}

//checks digital code to process specific transaction
void TransactionProcessor::processTransaction(const std::string& transactionCode) {
    std::string digitCode = transactionCode.substr(0, 2);//

    if (digitCode != "10" && !isUserLoggedIn()) {
        std::cout << "Error: User must log in before processing transactions." << std::endl;
        return;
    }

    if (digitCode == "10") processLogin();// i'm not sure if there is a digital code for login
    else if (digitCode == "00") processLogout();
    else if (digitCode == "01") processCreate();
    else if (digitCode == "02") processDelete();
    else if (digitCode == "03") processSell();
    else if (digitCode == "04") processBuy();
    else if (digitCode == "05") processRefund();
    else if (digitCode == "06") processAddCredit();
        //else if (digitCode == "00") processEndOfSession(); should be part of process logout
    else std::cout << "Error: Invalid transaction code: " << digitCode << std::endl;
}

bool isAlphanumeric(const std::string& str) {//checks if string is alphanumeric
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isalnum(c); });
}

void TransactionProcessor::processCreate() { // checks user list
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before creating a new user account." << std::endl;
        return;
    }

    const User* currentUser = currentSession.getCurrentUser();

    if (currentUser && currentUser->getUserType() != "admin") {
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

    if (class fileManager::doesUserExists(newUsername)) {
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
    fileManager.writeTransactionFile(transactionCode);

    User newUser(newUsername, userType);
    fileManager.addUser(newUser);
    fileManager.writeUsersFile();

    std::cout << "User account '" << newUsername << "' successfully created." << std::endl;
    logTransaction("Create transaction processed successfully");
}

void TransactionProcessor::processDelete() { //checks user list for username
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before deleting a user account." << std::endl;
        return;
    }

    const User* currentUser = currentSession.getCurrentUser();

    if (currentUser && currentUser->getUserType() != "admin") {
        std::cout << "Error: Only admin users can delete user accounts." << std::endl;
        return;
    }

    std::string usernameToDelete;
    std::cout << "Enter the username to delete: ";
    std::getline(std::cin, usernameToDelete);

    if (!fileManager.doesUserExists(usernameToDelete)) {
        std::cout << "Error: User '" << usernameToDelete << "' does not exist." << std::endl;
        return;
    }

    if (usernameToDelete == currentSession.currentUser.getUsername()) {
        std::cout << "Error: Cannot delete the current user's account." << std::endl;
        return;
    }

    std::string transactionCode = "02_" + usernameToDelete;
    fileManager.writeToDailyTransactionFile(transactionCode);

    fileManager.removeUser(usernameToDelete);
    fileManager.writeUsersFile();
    std::cout << "User account '" << usernameToDelete << "' successfully deleted." << std::endl;
    logTransaction("Delete transaction processed successfully");
}

void TransactionProcessor::processSell() { // checks game list, and user type
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before selling a game." << std::endl;
        return;
    }

    const User* currentUser = currentSession.getCurrentUser();

    if (currentUser && currentUser->getUserType() == "buy-standard"||"BS") {
        std::cout << "Error: buy-standard users cannot sell games." << std::endl;
        return;
    }

    std::string gameName;
    std::cout << "Enter the game name (up to 25 characters): ";
    std::getline(std::cin, gameName);

    if (gameName.length() > 25) {
        std::cout << "Error: Maximum length for a game name is 25 characters." << std::endl;
        return;
    }

    double price;
    std::cout << "Enter the price for the game (in dollars, e.g., 15.00): ";
    std::cin >> price;

    if (price <= 0 || price > 999.99) {
        std::cout << "Error: Invalid price. Price must be between 0.01 and 999.99." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string transactionCode = "03_" + gameName + "_" + currentSession.currentUser.getUsername() + "_" + std::to_string(price);
    FileManager.writeTransactionFile(transactionCode);

    Game updatedGame(gameName, currentSession.currentUser.getUsername(), price);
    FileManager.updateGamesFile(updatedGame);

    logTransaction("Game successfully listed for sale.");
}

void TransactionProcessor::processBuy() {// checks available game list, as well as username, user type, and balance
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before making a purchase." << std::endl;
        return;
    }

    if (currentSession.currentUser.getUserType() == "standard-sell") {
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

    double gamePrice = FileManager.getGamePrice(gameName);

    if (currentSession.currentUser.getAccountBalance() < gamePrice) {
        std::cout << "Error: Insufficient funds. You do not have enough money to purchase the game." << std::endl;
        return;
    }

    if (currentSession.currentUser.ownsGame(gameName)) {
        std::cout << "Error: You already own a copy of the game '" << gameName << "'." << std::endl;
        return;
    }

    currentSession.currentUser.deductAmount(gamePrice);
    fileManager.getUserByUsername(sellerName).creditAmount(gamePrice);
    currentSession.currentUser.addGameToCollection(gameName);

    std::string transactionCode = "04_" + gameName + "_" + sellerName + "_" + currentSession.currentUser.getUsername() + "_" + std::to_string(gamePrice);
    fileManager.writeTransactionFile(transactionCode);

    std::cout << "Purchase successful. You now own the game '" << gameName << "'." << std::endl;
    logTransaction("Buy transaction processed successfully");
}

void TransactionProcessor::processRefund() {// should check user list for user information like username and balance/credits
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before processing a refund." << std::endl;
        return;
    }

    if (currentSession.currentUser.getUserType() != "admin") {
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
    fileManager.writeToDailyTransactionFile(transactionCode);

    std::cout << "Refund successful. $" << creditAmount << " credited from '" << sellerName << "' to '" << buyerName << "'." << std::endl;
    logTransaction("Refund transaction processed successfully");
}

void TransactionProcessor::processAddCredit() {// checks username, user type, and balance/credits
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before adding credit." << std::endl;
        return;
    }

    if (currentSession.currentUser.getUserType() != "admin") {
        std::cout << "Error: Only admins are allowed to add credit." << std::endl;
        return;
    }

    std::string username;
    if (currentSession.currentUser.getUserType() == "admin") {
        std::cout << "Enter the username of the account to which credit is being added: ";
        std::getline(std::cin, username);

        if (!fileManager.isUserExists(username)) {
            std::cout << "Error: User '" << username << "' does not exist." << std::endl;
            return;
        }
    }
    else {
        username = currentSession.currentUser.getUsername();
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
    fileManager.writeToDailyTransactionFile(transactionCode);

    std::cout << "Credit added successfully. $" << creditAmount << " credited to '" << username << "'." << std::endl;
    logTransaction("Add credit transaction processed successfully");
}

void TransactionProcessor::processList() { //displays all purchasable games, with game info
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

void TransactionProcessor::processUserList() {// checks the active user list, and account info username, user type, balance/credits
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before viewing the user list." << std::endl;
        return;
    }


    if (currentUser && currentUser->getUserType() != "admin") {
        std::cout << "Error: User must be an admin to view the user list." << std::endl;
        return;
    }

    std::vector<User> usersFile = fileManager.getActiveUsers();

    std::cout << "List of Active Users:" << std::endl;
    std::cout << "---------------------" << std::endl;

    for (const auto& user : usersFile) {
        std::cout << "Username: " << user.getUsername() << std::endl;
        std::cout << "Account Type: " << user.getUserType() << std::endl;
        std::cout << "Credit: $" << user.getBalance() << std::endl;
        std::cout << "---------------------" << std::endl;
    }

    logTransaction("User List transaction processed successfully");
}

void TransactionProcessor::processEndOfSession() {//should be part of log out
    if (!isUserLoggedIn()) {
        std::cout << "Error: User must log in before ending the session." << std::endl;
        return;
    }

    std::vector<std::string> sessionTransactions = fileManager.getSessionTransactions();
    writeDailyTransactionFile(sessionTransactions);

    std::cout << "End of session. Daily transactions logged." << std::endl;

    currentSession.endSession();
    logTransaction("End of Session transaction processed successfully");
}

void TransactionProcessor::processLogin() {//checks for user, as well as defines the usertype in the given session, can change this to be simpler
    if (isUserLoggedIn()) {
        std::cout << "Error: User '" << currentSession.getCurrentUser() << "' is already logged in." << std::endl;
        return;
    }

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    if (fileManager.doesUserExists(username)) {
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
    const User* currentUser = currentSession.getCurrentUser();

    std::cout << "Logout successful. Goodbye, " << currentSession.getCurrentUser() << "!" << std::endl;
    currentSession.endSession();
    logTransaction("Logout transaction processed successfully");
}
//to write the daily transaction file and should should be part of log out
void TransactionProcessor::writeDailyTransactionFile(const std::vector<std::string>& transactions) {
    std::ofstream dailyTransactionFile(FileManager.getDailyTransactionFilePath(), std::ios_base::app);

    if (fileManager::readTransactionsFile.is_open()) {
        for (const auto& transaction : transactions) {
            dailyTransactionFile << transaction << std::endl;
        }
    }
    else {
        std::cerr << "Error: Unable to open daily transaction file for writing." << std::endl;
    }

    dailyTransactionFile.close();
}
//might not need this, but it was to log the transactions in the given session
void TransactionProcessor::logTransaction(const std::string& logMessage) const {
    std::ofstream logFile(FileManager.getLogFilePath(), std::ios_base::app);

    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Error: Unable to open log file for writing." << std::endl;
    }
}
