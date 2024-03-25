import pytest
from Game import Game

# Test cases for Game class
class TestGame:
    def test_get_name(self, capsys):
        # Test data
        game = Game("Test Game", "Test Seller", 50)

        # Call getName method
        game.getName()

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "Test Game"

    def test_get_price(self, capsys):
        # Test data
        game = Game("Test Game", "Test Seller", 50)

        # Call getPrice method
        game.getPrice()

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "50"

    def test_get_seller(self, capsys):
        # Test data
        game = Game("Test Game", "Test Seller", 50)

        # Call getSeller method
        game.getSeller()

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "Test Seller"
