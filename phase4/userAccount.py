class userAccount:
    def __init__(self, userName, balance, userType, gameCollection=None):
        self.userName=userName
        self.balance=balance
        self.userType=userType
        self.gameCollection=gameCollection

    def depositBalance(self, balance):
        self.balance+=balance

    def withdrawBalance(self, balance):
        self.balance -= balance

    def getUserCollection(self):
        self.gameCollection.listCollection