class ErrorLogger:
    errors=[]
    
    def recordError(self,error):
        self.errors.append(error)
        
    def displayError(self):
        print(self.errors)

def main():
    errorLogger = ErrorLogger()
    errorLogger.recordError("Error: File not found")
    errorLogger.displayError()

if __name__ == "__main__":
    main()