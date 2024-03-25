import pytest
from ErrorLogger import ErrorLogger

# Test cases for ErrorLogger class
class TestErrorLogger:
    def test_record_error(self):
        logger = ErrorLogger()
        logger.recordError("Error 1")
        assert logger.errors == ["Error 1"]

    def test_display_error(self, capsys):
        logger = ErrorLogger()
        logger.recordError("Error 1")
        logger.displayError()
        captured = capsys.readouterr()
        assert captured.out == "['Error 1']\n"

    def test_record_error_with_wrong_input(self):
        logger = ErrorLogger()
        with pytest.raises(TypeError):
            logger.recordError(123)  # Passing an integer instead of a string should raise a TypeError

    def test_display_error_without_errors(self, capsys):
        logger = ErrorLogger()
        logger.displayError()