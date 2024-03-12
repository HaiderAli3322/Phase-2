class Game:
    price=0
    name=""
    seller=""
    def __init__(self, name, seller, price):
        self.name =name
        self.seller=seller
        self.price = price
    
    def getName(self):
        print(self.name)

    def getPrice(self):
        print(self.price)

    def getSeller(self):
        print(self.seller)

    
    
        