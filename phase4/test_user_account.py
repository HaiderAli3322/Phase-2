import pytest
from userAccount import UserAccount

# Test cases for UserAccount class
class TestUserAccount:
    def test_deposit_balance(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")
        deposit_amount = 50

        # Perform deposit
        user.depositBalance(deposit_amount)

        # Assert balance
        assert user.balance == 100 + deposit_amount

    def test_withdraw_balance(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")
        withdrawal_amount = 50

        # Perform withdrawal
        user.withdrawBalance(withdrawal_amount)

        # Assert balance
        assert user.balance == 100 - withdrawal_amount

    def test_get_user_collection(self):
        # Test data
        user = UserAccount("test_user", 100, "regular", ["Game1", "Game2", "Game3"])

        # Retrieve user collection
        collection = user.getUserCollection()

        # Assert collection
        assert collection == ["Game1", "Game2", "Game3"]

    def test_get_user_collection_no_collection(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")

        # Retrieve user collection
        collection = user.getUserCollection()

        # Assert collection is None
        assert collection is None

    def test_deposit_negative_amount(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")
        deposit_amount = -50

        # Attempt to deposit negative amount
        with pytest.raises(ValueError):
            user.depositBalance(deposit_amount)

    def test_withdraw_negative_amount(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")
        withdrawal_amount = -50

        # Attempt to withdraw negative amount
        with pytest.raises(ValueError):
            user.withdrawBalance(withdrawal_amount)

    def test_withdraw_more_than_balance(self):
        # Test data
        user = UserAccount("test_user", 100, "regular")
        withdrawal_amount = 150

        # Attempt to withdraw more than balance
        with pytest.raises(ValueError):
            user.withdrawBalance(withdrawal_amount)
