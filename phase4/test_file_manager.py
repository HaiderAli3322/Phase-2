import pytest
from FileManager import FileManager

# Test cases for FileManager class
class TestFileManager:
    def test_read_file(self):
        # Test data
        file_path = "test_file.txt"
        file_content = "Test file content."

        # Create a file with test content
        with open(file_path, "w") as file:
            file.write(file_content)

        # Create an instance of FileManager
        file_manager = FileManager(file_path)

        # Read file content
        read_content = file_manager.readFile(file_path)

        # Assert content
        assert read_content == file_content

    def test_log_error(self):
        # Test data
        file_path = "error_log.txt"
        error_message = "Test error message."

        # Create an instance of FileManager
        file_manager = FileManager(file_path)

        # Log error
        file_manager.logError(file_path, error_message)

        # Read content from the file and assert
        with open(file_path, "r") as file:
            logged_error = file.read()
            assert logged_error == error_message

    def test_update_file(self):
        # Test data
        file_path = "test_file.txt"
        existing_content = "Existing content.\n"
        transaction = "Test transaction."

        # Create a file with existing content
        with open(file_path, "w") as file:
            file.write(existing_content)

        # Create an instance of FileManager
        file_manager = FileManager(file_path)

        # Update file with transaction
        file_manager.updateFile(file_path, transaction)

        # Read content from the file and assert
        with open(file_path, "r") as file:
            updated_content = file.read()
            assert updated_content == existing_content + transaction
