class game:
    def __init__(self,gameName,seller,price):
        self.gameName=gameName
        self.seller=seller
        self.price=price


    def updateGame(self,gameName,seller,price):
        self.gameName=gameName
        self.seller=seller
        self.price=price
    
    def getName(self):
        print(self.gameName)
    
    def getSeller(self):
        print(self.seller)

    def getName(self):
        print(self.price)



        