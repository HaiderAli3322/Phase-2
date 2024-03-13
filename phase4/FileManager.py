class FileManager:
    filePath=""
    
    def __init__(self,filePath):
        self.filePath=filePath
        
    def readFile(self,fileName):
        ##get file name most likely from file path 
        
        f = open(fileName,"r")
        print(f.read)
        f.close()
        
    def logError(self,fileName,error):
        f= open(fileName,"a")
        f.write(error)
        f.close
    
    def updateFile(self,fileName,transaction):
        f=open(fileName,"a")
        f.write(transaction)
        f.close