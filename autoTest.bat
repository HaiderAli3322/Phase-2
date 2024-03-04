@echo off
setlocal EnableDelayedExpansion

:: Define the path to the main script and the users file for easy modification
set MAIN_SCRIPT_PATH=FrontEnd.bat
set USERS_FILE_PATH=users.txt
set DAILY_TRANSACTION_FILE=daily_transactions.txt

:: Clean up before tests
echo Cleaning up before tests...
del "%USERS_FILE_PATH%" 2>nul
del "%DAILY_TRANSACTION_FILE%" 2>nul
(echo admin
echo k
echo s
echo t) > "%USERS_FILE_PATH%"

:: Start testing
echo Starting tests...

:: Test 1: Login as admin
echo Testing Login functionality...
(
  echo 1
  echo admin
) > temp_input.txt

call %MAIN_SCRIPT_PATH% < temp_input.txt > temp_output.txt

:: Display temp_input.txt content for debugging purposes
type temp_input.txt

:: Display temp_output.txt content for debugging purposes
type temp_output.txt

:: Check if the login was successful
findstr /C:"Login successful. Welcome, admin" temp_output.txt > nul
if !errorlevel! == 0 (
  echo Test 1 Passed: Login as admin successful.
) else (
  echo Test 1 Failed: Login as admin not successful.
)

:: Test 2: Create a new user as admin
echo Testing Create functionality...
(
echo 3
echo newUser
echo full-standard
echo 9
) > temp_input.txt
call %MAIN_SCRIPT_PATH% < temp_input.txt > temp_output.txt
findstr /C:"newUser full-standard" "%USERS_FILE_PATH%" > nul
if !errorlevel! == 0 (
    echo Test 2 Passed: New user creation as admin successful.
) else (
    echo Test 2 Failed: New user creation as admin not successful.
)

:: Test 3: Logout
echo Testing Logout functionality...
echo 2 > temp_input.txt
call %MAIN_SCRIPT_PATH% < temp_input.txt > temp_output.txt
findstr /C:"Logout successful. Goodbye, admin." temp_output.txt > nul
if !errorlevel! == 0 (
    echo Test 3 Passed: Logout successful.
) else (
    echo Test 3 Failed: Logout not successful.
)

:: Cleanup
echo Cleaning up...
del temp_input.txt
del temp_output.txt

echo Tests completed.
pause
endlocal