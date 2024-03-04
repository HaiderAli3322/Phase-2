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

if "!choice!"=="1" (
    goto login
) else if "!choice!"=="2" (
    goto logout
) else if "!choice!"=="3" (
    goto create
) else if "!choice!"=="4" (
    goto delete
) else if "!choice!"=="5" (
    goto sell
) else if "!choice!"=="6" (
    goto buy
) else if "!choice!"=="7" (
    goto refund
) else if "!choice!"=="8" (
    goto addcredit
) else if "!choice!"=="9" (
    goto end
) else (
    echo Invalid choice, please try again.
    goto main
)

:login
echo Current users:
type "users.txt"
echo.
echo Enter your username:
set /p username=
findstr /x /m "!username!" "users.txt" > nul
if !errorlevel! == 0 (
    echo Login successful. Welcome, !username!
    set loggedIn=1
    set loggedInUser=!username!
) else (
    echo Login failed. Username not found.
)
goto main




:logout
if not defined loggedIn (
    echo You must be logged in to logout.
    goto main
)

echo Writing to daily transaction file...
echo Logout successful. Goodbye, !username!.
set loggedIn=
set username=
goto main

:create
if not "!loggedInUser!"=="admin" (
    echo This operation is only available to admin users.
    goto main
)

echo Enter new username (max 15 chars):
set /p newUsername=

echo Entered Username: '!newUsername!'


echo !newUsername! | findstr /R "^...............$" > nul && (
    echo Username too long
    goto create
)

findstr /x /m "!newUsername!" "users.txt" > nul && (
    echo Username already exists
    goto create
)

echo Enter type of user (admin, full-standard, buy-standard, sell-standard):
set /p userType=


echo !newUsername! >> "users.txt"

echo Adding to users.txt: !newUsername!

goto main
:delete

if not "!loggedInUser!"=="admin" (
    echo This operation is only available to admin users.
    goto main
)
echo Enter the username to delete: 
set /p usernameToDelete=
findstr /x /m "!usernameToDelete!" "users.txt" > nul
if !errorlevel! NEQ 0 (
    echo User does not exist.
    goto main
)
echo Delete !usernameToDelete! >> daily_transactions.txt
echo User !usernameToDelete! successfully deleted.
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
set gamePrice=50
set userCredits=100

if %userCredits% LSS %gamePrice% (
    echo You do not have enough credits to buy this game.
    goto main
)

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
