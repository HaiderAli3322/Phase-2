@echo off
setlocal enabledelayedexpansion

:main
echo Welcome to the Front End Session Simulator
echo Please choose a transaction:
echo 1. Login
echo 2. Logout
echo 3. Create
echo 4. Delete
echo 5. Sell
echo 6. Buy
echo 7. Refund
echo 8. AddCredit
echo 9. Exit
set /p choice=Enter your choice: 

if "!choice!"=="1" goto login
if "!choice!"=="2" goto logout
if "!choice!"=="3" goto create
if "!choice!"=="4" goto delete
if "!choice!"=="5" goto sell
if "!choice!"=="6" goto buy
if "!choice!"=="7" goto refund
if "!choice!"=="8" goto addcredit
if "!choice!"=="9" goto end

echo Invalid choice, please try again.
goto main

:login
set /p username=Enter your username: 

REM Assuming users.txt contains a list of valid usernames, one per line
findstr /x /m "!username!" users.txt > nul
if %errorlevel% == 0 (
    echo Login successful. Welcome, !username!
    REM Set a flag indicating the user is logged in
    set loggedIn=1
    REM Proceed with loading games file or other initializations here
) else (
    echo Login failed. Username not found.
)

goto main


:logout
if not defined loggedIn (
    echo You must be logged in to logout.
    goto main
)

REM Perform any necessary cleanup actions here
echo Writing to daily transaction file...
REM Placeholder for command to write logout transaction to a file

echo Logout successful. Goodbye, %username%.
set loggedIn=
set username=
goto main


:create
if "%loggedIn%" NEQ "admin" (
    echo This operation is only available to admin users.
    goto main
)

set /p newUsername=Enter new username (max 15 chars): 
REM Validate new username length and uniqueness
echo %newUsername% | findstr /R "^..............." > nul && echo Username too long && goto create
findstr /x /m "%newUsername%" users.txt > nul && echo Username already exists && goto create

set /p userType=Enter type of user (admin, full-standard, buy-standard, sell-standard): 
REM Validate user type
if "%userType%" NEQ "admin" if "%userType%" NEQ "full-standard" if "%userType%" NEQ "buy-standard" if "%userType%" NEQ "sell-standard" (
    echo Invalid user type.
    goto create
)

REM Assuming daily transaction file setup
echo Create %newUsername% %userType% >> daily_transactions.txt
echo User %newUsername% created as %userType%.
goto main


:delete
if "%loggedIn%" NEQ "admin" (
    echo This operation is only available to admin users.
    goto main
)

set /p usernameToDelete=Enter the username to delete: 
findstr /x /m "%usernameToDelete%" users.txt > nul
if %errorlevel% NEQ 0 (
    echo User does not exist.
    goto main
)

echo Delete %usernameToDelete% >> daily_transactions.txt
echo User %usernameToDelete% successfully deleted.
goto main


:sell
if not defined loggedIn (
    echo You must be logged in to sell a game.
    goto main
)
if "%userType%"=="buy-standard" (
    echo Buy-standard users cannot sell games.
    goto main
)
set /p gameName=Enter the game name: 
set /p price=Enter the price for the game: 
echo Sell %gameName% %price% >> daily_transactions.txt
echo %gameName% is now available for sale at %price%.
goto main


:buy
if not defined loggedIn (
    echo You must be logged in to buy a game.
    goto main
)
if "%userType%"=="sell-standard" (
    echo Sell-standard users cannot buy games.
    goto main
)

set /p gameName=Enter the game name you wish to purchase: 
REM Placeholder for fetching game price and user's available credits
set gamePrice=50
set userCredits=100

if %userCredits% LSS %gamePrice% (
    echo You do not have enough credits to buy this game.
    goto main
)

REM Deduct gamePrice from userCredits here
echo Buy %gameName% >> daily_transactions.txt
echo You have bought %gameName%.
goto main


:refund
if "%loggedIn%" NEQ "admin" (
    echo This operation is only available to admin users.
    goto main
)
set /p buyerUsername=Enter the buyer's username: 
set /p sellerUsername=Enter the seller's username: 
set /p amount=Enter the amount to refund: 
echo Refund %buyerUsername% %sellerUsername% %amount% >> daily_transactions.txt
echo Refund of %amount% from %sellerUsername% to %buyerUsername% processed.
goto main


:addcredit
if not defined loggedIn (
    echo You must be logged in to add credit.
    goto main
)
set /p amount=Enter the amount of credit to add: 
if "%userType%"=="admin" (
    set /p username=Enter the username to which credit is being added: 
) else (
    set username=%loggedInUser%
)
echo AddCredit %username% %amount% >> daily_transactions.txt
echo Added %amount% credit to %username%.
goto main


:end
echo Exiting...
endlocal
