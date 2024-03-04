@echo off
setlocal enabledelayedexpansion

:main

if !loggedIn! equ 1 (
	for /f "tokens=1,* delims=:" %%A in ('findstr /i /n /c:"!username!" "users.txt"') do (
         set "loggedIn=1"
         set lineParsedInLog=%%B
	)
    for /f "tokens=1-3 delims=_" %%A in ("!lineParsedInLog!") do (
        set "authority=%%A"
        set "username=%%B"
        set "credit=%%C"
    )
echo.
echo.
echo Welcome !username!
echo Authority !authority!
echo Credits !credit!
echo.
echo.
)

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




for /f "tokens=1,* delims=:" %%A in ('findstr /i /n /c:"!username!" "users.txt"') do (
    
        
        set "loggedIn=1"
        set lineParsedInLog=%%B
	
        goto :setLogInfo
)


echo Login failed. Username not found.
goto :main

:setLogInfo

for /f "tokens=1-3 delims=_" %%A in ("!lineParsedInLog!") do (
    
    set "authority=%%A"
    set "username=%%B"
    set "credit=%%C"
)


goto :main

:logout
if not defined loggedIn (
    echo You must be logged in to logout.
    goto main
)

echo Logout successful. Goodbye, !username!.
set loggedIn=
set username=
set authority=
set credit=
set lineParsedInLog=
goto main

:create
if not "!authority!"=="AA" (
    echo This operation is only available to admin users.
    goto main
)

set /p "newUsername=Enter new username (max 15 chars): "


set "usernameLength=0"
for /l %%A in (0,1,15) do (
    set "char=!newUsername:~%%A,1!"
    if defined char (
        set /a "usernameLength+=1"
    ) 
)

if %usernameLength% gtr 15 (
    echo Username exceeds the maximum length of 15 characters. Please try again.
    goto :create
)

for /f "tokens=2 delims=_" %%A in ('type "users.txt"') do (
    if /i "%%A"=="!newUsername!" (
        
        echo Username already exists. Please choose a different one.
        goto :create
    )
)


echo Entered Username: '!newUsername!'
goto :enterUserType
:enterUserType  

echo Enter type of user (AA(admin), (FS)full-standard, (BS)buy-standard, (SS)sell-standard):
set /p input=

for /f "usebackq delims=" %%I in (`powershell "\"!input!\".toUpper()"`) do set "userType=%%~I"

if /i "!userType!"=="AA" (
    echo Admin user type selected.
) else if /i "!userType!"=="FS" (
    echo Full-Standard user type selected.
) else if /i "!userType!"=="BS" (
    echo Buy-Standard user type selected.
) else if /i "!userType!"=="SS" (
    echo Sell-Standard user type selected.
) else (
    echo Invalid user type. Please enter a valid user type.
    goto :enterUserType
)


echo !userType!_!newUsername!_000000 >> "users.txt"

echo Adding to users.txt: !newUsername!

goto main
:delete

if not "!authority!"=="AA" (
    echo This operation is only available to admin users.
    goto main
)
echo Enter the username to delete:
set /p "deleteUsername="

rem Check if the user exists in users.txt
set "userExists="
for /f "tokens=2 delims=_" %%A in ('type "users.txt"') do (
    if /i "%%A"=="!deleteUsername!" (
        set "userExists=1"

    )
)

if not defined userExists (
    echo User not found. Deletion aborted.
    goto :delete
)

set "tempFile=%temp%\tempUsers.txt"

rem Iterate over the lines and exclude the line with the specified username
(for /f "tokens=*" %%A in ('type "users.txt" ^| find /v /i "!deleteUsername!"') do (
    echo %%A
)) > "%tempFile%"

rem Overwrite users.txt with tempUsers.txt
copy /y "%tempFile%" "users.txt" > nul
echo.
echo.
echo User deleted successfully.
echo.
echo.

goto :main

:sell
if not defined loggedIn (
    echo You must be logged in to sell a game.
    goto main
)
if "%authority%"=="BS" (
    echo Buy-standard users cannot sell games.
    goto main
)

set /p "newGame=Enter the Game name (max 16 chars): "


set "gameNameLength=0"
for /l %%A in (0,1,16) do (
    set "char=!newGame:~%%A,1!"
    if defined char (
        set /a "gameNameLength+=1"
    ) 
)

if %gameNameLength% gtr 16 (
    echo game name exceeds the maximum length of 16 characters. Please try again.
    goto :sell
)

for /f "tokens=2 delims=_" %%A in ('type "gameSale.txt"') do (
    if /i "%%A"=="!newGame!" (
        
        echo game already exists. Please choose a different one.
        goto :sell
    )
)
set /p "sellPrice=Enter the sell price (between 10 and 1000): "

rem Validate the entered price (optional)
set /a sellPrice+=0
if %sellPrice% lss 10 (
    echo Invalid price. Sell price must be at least 10.
    goto :sell
)
if %sellPrice% gtr 1000 (
    echo Invalid price. Sell price must not exceed 1000.
    goto :sell
)

echo Adding !newGame! to the sale list with price !sellPrice!.
(echo !newGame!_%username%_!sellPrice!)>> "gameSale.txt"

goto main

:buy
if not defined loggedIn (
    echo You must be logged in to buy a game.
    goto main
)
if "%userType%"=="SS" (
    echo Sell-standard users cannot buy games.
    goto main
)

set /p gameName=Enter the game name you wish to purchase: 
set "price="
set "foundGame="

rem Iterate through gameSale.txt
for /f "tokens=1-3 delims=_" %%A in (gameSale.txt) do (
    if /i "%%A"=="!gameName!" (
        set "foundGame=1"
        set "sellerName=%%B"
        set "price=%%C"
        
    )
)

if not defined foundGame (
    echo Game not found in the sale list.
    goto :buy
)

echo The price of !gameName! is: !price!

if !credit! lss !price! (
    echo credits = !credit!
    echo Insufficient credits. Transaction aborted.
    goto :buy
)

rem Update the seller's credits
for /f "delims=" %%X in ('type "users.txt" ^| find /i "!sellerName!"') do (
    set "sellerLine=%%X"
    for /f "tokens=1,* delims=_" %%A in ("!sellerLine!") do (
        set "sellerCredit=%%C"
        set /a "newSellerCredit=sellerCredit+price"
        set "sellerLine=%%A_!sellerName!_!newSellerCredit!"
	echo new seller stuff "sellerLine=%%A_!sellerName!_!newSellerCredit!"
    )
)

rem Update the current user's credits
for /f "delims=" %%X in ('type "users.txt" ^| find /i "%username%"') do (
    set "currentUserLine=%%X"
    for /f "tokens=1,* delims=_" %%A in ("!currentUserLine!") do (
        set "currentUserCredit=!credit!"
        set /a "credit=currentUserCredit-price"
        set "currentUserLine=%%A_%username%_!newCurrentUserCredit!"
	echo current user stuff "currentUserLine=%%A_%username%_!credit!"
    )
)
set "tempFile=%temp%\tempUsers.txt"
set "tempFileGameSale=%temp%\tempGameSale.txt"
set "userExists="
(for /f "tokens=1-3 delims=_" %%A in ('type "users.txt"') do (
    if /i "%%B"=="!sellerName!" (
        set /a "newCredit=%%C+price"
        echo %%A_%%B_!newCredit!
        set "userExists=1"
    ) else if /i "%%B"=="%username%" (
        set /a "newCredit=%%C-price"
        echo %%A_%%B_!newCredit!
        set "userExists=1"
    ) else (
        echo %%A_%%B_%%C
    )
)) > "%tempFile%"

(for /f "tokens=1,2,3 delims=_" %%D in ('type "gameSale.txt"') do (
    if /i "%%D"=="!gameName!" (
        set "gamePurchased=1"
    ) else (
        echo %%D_%%E_%%F
    )
)) > "%tempFileGameSale%"

if not defined gamePurchased (
    echo GameType_%gameName%_%sellerName%_%price% >> "%tempFileGameSale%"
)

if not defined userExists (
    echo UserType_%username%_%credit% >> "%tempFile%"
)

move /y "%tempFile%" "users.txt" > nul
move /y "%tempFileGameSale%" "gameSale.txt" > nul

echo Transaction successful. Credits updated.
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

if "%Authority%"=="AA" (
    set /p userGettingMoney=Enter the username to which credit is being added: 
) else (
    set userGettingMoney=%username%
)

rem Validate the entered amount (optional)
set /a amount+=0
if %amount% leq 0 (
    echo Invalid amount. Credit must be a positive number.
    goto main
)

rem Set the temporary file path
set "tempFile=%temp%\tempUsers.txt"

rem Ensure that the %temp% directory exists
if not exist "%temp%" mkdir "%temp%"

rem Update the users.txt file with the new credit
(for /f "tokens=1-3 delims=_" %%A in ('type "users.txt"') do (
    set "inputType=%%A"
    set "inputUsername=%%B"
    set "inputCredit=%%C"

    rem Skip processing if the line is empty
    if "%%A" neq "" (
        if /i "!inputUsername!"=="!userGettingMoney!" (
            set "userExists=1"
            set /a newCredit=inputCredit+amount
            echo !inputType!_!inputUsername!_!newCredit! >> "%tempFile%"
        ) else (
            echo !inputType!_!inputUsername!_!inputCredit! >> "%tempFile%"
        )
    )
)) > nul

if not defined userExists (
    echo UserType_!userGettingMoney!_!amount! >> "%tempFile%"
)

rem Overwrite users.txt with tempUsers.txt
move /y "%tempFile%" "users.txt" > nul

echo Added %amount% credit to %userGettingMoney%.
goto main

:end
echo Exiting...
endlocal
