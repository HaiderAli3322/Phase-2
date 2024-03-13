class ErrorLogger:
    errors=[]
    
    def recordError(self,error):
        self.errors.append(error)
        
    def displayError(self):
        print(self.errors)