class TransactionProcessor:
    transaction=""
    
    def __init__(self,transaction):
        self.transaction=transaction
        
    def writeTransaction(self,transaction,fileName):
        f = open(fileName,"a")
        f.write(transaction)
        f.close


def main():
    transaction = "John Doe has deposited $500\n"
    transaction2 = "John Doe purchased Minecraft for $26.95 USD\n"
    processor = TransactionProcessor(transaction)
    processor2 = TransactionProcessor(transaction2)
    processor.writeTransaction(transaction,"transactions.txt")
    processor2.writeTransaction(transaction2,"transactions.txt")

if __name__ == "__main__":
    main()