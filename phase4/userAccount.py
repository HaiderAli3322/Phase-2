class UserAccount:
    def __init__(self, userName, balance, userType, gameCollection=None):
        self.userName = userName
        self.balance = balance
        self.userType = userType
        self.gameCollection = gameCollection

    def depositBalance(self, amount):
        if amount < 0:
            raise ValueError("Deposit amount must be positive")
        self.balance += amount

    def withdrawBalance(self, amount):
        if amount < 0:
            raise ValueError("Withdrawal amount must be positive")
        if amount > self.balance:
            raise ValueError("Withdrawal amount exceeds balance")
        self.balance -= amount

    def getUserCollection(self):
        return self.gameCollection

def main():
    user1 = UserAccount("JohnDoe", 1000, "Premium", ["The Witcher", "Valorant", "Minecraft"])

    print("Username:", user1.userName)
    print("Balance:", user1.balance)
    print("User Type:", user1.userType)
    print("Game Collection:", user1.getUserCollection())

    try:
        user1.depositBalance(500)
        user1.withdrawBalance(200)
    except ValueError as e:
        print("Error:", e)

    print("Updated Balance:", user1.balance)

if __name__ == "__main__":
    main()
