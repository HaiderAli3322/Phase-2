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
    games_collection.listCollection()
    games_collection.addToCollection("Rocket League")
    print("\nUpdated Game Collection:")
    games_collection.listCollection()
    games_collection.removeFromCollection("Valorant")
    print("\nUpdated Game Collection after removing Valorant:")
    games_collection.listCollection()
    games_collection.removeFromCollection("Fifa 24")

if __name__ == "__main__":
    main()
