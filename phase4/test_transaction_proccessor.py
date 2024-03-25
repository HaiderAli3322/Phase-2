import pytest
from TransactionProcessor import TransactionProcessor

# Test cases for TransactionProcessor class
class TestTransactionProcessor:
    @staticmethod
    def read_file_content(file_name):
        with open(file_name, "r") as file:
            return file.read()

    def test_write_transaction(self):
        # Test data
        transaction = "Test transaction data."
        file_name = "test_transactions.txt"

        # Create an instance of TransactionProcessor
        processor = TransactionProcessor(transaction)

        # Write transaction to file
        processor.writeTransaction(transaction, file_name)

        # Read content from the file and assert
        content = self.read_file_content(file_name)
        assert content == transaction

    def test_append_multiple_transactions(self):
        # Test data
        transactions = ["Transaction 1", "Transaction 2", "Transaction 3"]
        file_name = "test_transactions.txt"

        # Create an instance of TransactionProcessor
        processor = TransactionProcessor("")

        # Write transactions to file
        for transaction in transactions:
            processor.writeTransaction(transaction + "\n", file_name)

        # Read content from the file and assert
        content = self.read_file_content(file_name)
        assert content == "\n".join(transactions) + "\n"

    def test_write_empty_transaction(self):
        # Test data
        transaction = ""
        file_name = "test_transactions.txt"

        # Create an instance of TransactionProcessor
        processor = TransactionProcessor("")

        # Write empty transaction to file
        processor.writeTransaction(transaction, file_name)

        # Read content from the file and assert
        content = self.read_file_content(file_name)
        assert content == transaction

    def test_write_to_existing_file(self):
        # Test data
        transaction = "Test transaction data."
        file_name = "existing_transactions.txt"

        # Create a file with existing content
        with open(file_name, "w") as file:
            file.write("Existing content\n")

        # Create an instance of TransactionProcessor
        processor = TransactionProcessor(transaction)

        # Write transaction to existing file
        processor.writeTransaction(transaction, file_name)

        # Read content from the file and assert
        content = self.read_file_content(file_name)
        assert content.strip() == "Existing content\n" + transaction

    def test_write_transaction_invalid_file(self):
        # Test data
        transaction = "Test transaction data."
        file_name = "nonexistent_directory/test_transactions.txt"

        # Create an instance of TransactionProcessor
        processor = TransactionProcessor(transaction)

        # Write transaction to non-existent directory
        with pytest.raises(Exception):
            processor.writeTransaction(transaction, file_name)
