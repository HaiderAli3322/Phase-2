class TransactionProcessor:
    transaction=""
    
    def __init__(self,transaction):
        self.transaction=transaction
        
    def writeTransaction(self,transaction,fileName):
        f = open(fileName,"a")
        f.write(transaction)
        f.close
        
    