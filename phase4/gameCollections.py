class GameCollections:
    games=[]
    def __init__(self,gameList):
        self.games=gameList


    def removeFromCollection(self,gameName):
        self.games.pop(gameName)

    def addToCollection(self,game):
        self.games.append(game)
    
    def listCollection(self):
        print(self.games)
