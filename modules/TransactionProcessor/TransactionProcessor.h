#ifndef TRANSACTIONPROCESSOR_H
#define TRANSACTIONPROCESSOR_H

#include <string>
#include <vector>

// Forward declarations
class FileManager;
class Session;

class TransactionProcessor {
private:
    FileManager& fileManager;  // Reference to FileManager object
    Session& currentSession;   // Reference to Session object
    bool isLoggedIn;

    // Private helper method to check if a user is logged in
    bool isUserLoggedIn() const;
public:
    // Constructor with references to FileManager and Session objects
    TransactionProcessor(FileManager& fm, Session& session);

    // Method to process a transaction
    void processTransaction(const std::string& transactionCode);

private:
    // Private helper methods for each transaction type
    void processLogin();
    void processLogout();
    void writeDailyTransactionFile(const std::vector<std::string>& transactions);
    void logTransaction(const std::string& logMessage) const;
    void processCreate();
    void processDelete();
    void processSell();
    void processBuy();
    void processRefund();
    void processAddCredit();
    void processList();
    void processUserList();
    void processEndOfSession();

};

#endif // TRANSACTIONPROCESSOR_H
