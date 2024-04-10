class GameCollections:
    def __init__(self, gameList):
        self.games = gameList

    def removeFromCollection(self, gameName):
        if gameName in self.games:
            self.games.remove(gameName)
        else:
            print(f"{gameName} is not in the collection.")

    def addToCollection(self, game):
        self.games.append(game)
        print(f"\nAdded {game} to the collection.")

    def listCollection(self):
        print(self.games)

def main():
    games_collection = GameCollections(["The Witcher", "Valorant", "Minecraft"])
    print("Initial Game Collection:")
    games_collection.addToCollection("test1")
    games_collection.listCollection()

if __name__ == "__main__":
    main()
