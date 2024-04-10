import pytest
from gameCollections import GameCollections

# Test cases for GameCollections class
class TestGameCollections:
    def test_remove_from_collection_existing_game(self, capsys):
        # Test data
        game_list = ["Game1", "Game2", "Game3"]
        game_collections = GameCollections(game_list)

        # Remove an existing game
        game_collections.removeFromCollection("Game2")

        # Assert the game is removed
        assert "Game2" not in game_collections.games

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == ""

    def test_remove_from_collection_non_existing_game(self, capsys):
        # Test data
        game_list = ["Game1", "Game2", "Game3"]
        game_collections = GameCollections(game_list)

        # Remove a non-existing game
        game_collections.removeFromCollection("Game4")

        # Assert nothing is removed
        assert game_collections.games == game_list

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "Game4 is not in the collection."

    def test_add_to_collection(self, capsys):
        # Test data
        game_list = ["Game1", "Game2", "Game3"]
        game_collections = GameCollections(game_list)

        # Add a new game
        game_collections.addToCollection("New Game")

        # Assert the game is added
        assert "New Game" in game_collections.games

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "Added New Game to the collection."

    def test_list_collection(self, capsys):
        # Test data
        game_list = ["Game1", "Game2", "Game3"]
        game_collections = GameCollections(game_list)

        # List the collection
        game_collections.listCollection()

        # Capture printed output
        captured = capsys.readouterr()

        # Assert printed output
        assert captured.out.strip() == "['Game1', 'Game2', 'Game3']"
