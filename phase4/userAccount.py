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
    
    def validateUser(self):
        if(len(self.userName)>16 or len(self.userName)<0):
            print("Invalid length of username")
        else:
            print("user is valid")

    def getUserCollection(self):
        self.gameCollection.listCollection