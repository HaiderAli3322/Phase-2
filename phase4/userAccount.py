class UserAccount:
    def __init__(self, userName, balance, userType, gameCollection=None):
        self.userName = userName
        self.balance = balance
        self.userType = userType
        self.gameCollection = gameCollection

    def depositBalance(self, amount):
        self.balance += amount

    def withdrawBalance(self, amount):
        self.balance -= amount

    def getUserCollection(self):
        return self.gameCollection

def main():
    
    user1 = UserAccount("JohnDoe", 1000, "Premium", ["The Witcher", "Valorant", "Minecraft"])

  
    print("Username:", user1.userName)
    print("Balance:", user1.balance)
    print("User Type:", user1.userType)
    print("Game Collection:", user1.getUserCollection())

    
    user1.depositBalance(500)
    user1.withdrawBalance(200)

   
    print("Updated Balance:", user1.balance)

if __name__ == "__main__":
    main()
