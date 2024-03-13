class Game:
    price = 0
    name = ""
    seller = ""

    def __init__(self, name, seller, price):
        self.name = name
        self.seller = seller
        self.price = price

    def getName(self):
        print(self.name)

    def getPrice(self):
        print(self.price)

    def getSeller(self):
        print(self.seller)


def main():
    
    game1 = Game("The Witcher 3: Wild Hunt", "CD Projekt Red", 59.99)

   
    print("Game Name:")
    game1.getName()

    print("Game Price:")
    game1.getPrice()

    print("Game Seller:")
    game1.getSeller()


if __name__ == "__main__":
    main()


    
    
        