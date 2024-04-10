#!/bin/bash




# Define paths for input data
output_dir="daily_outputs"




# Base name for the transaction files
transaction_file_base="DailyTransactionFile"




# Function to check for the next available transaction file number
function find_next_available_file {
local base_name=$1
local i=1
while true; do
 if [[ ! -e "$output_dir/$base_name$i.txt" ]]; then
 echo "$base_name$i.txt"
 return
 fi
 ((i++))
done
}




# Function to update availablegames.txt after a game is sold
function update_available_games {
local game_name=$1
local available_games_file="../test_data/availablegames_test.txt"




# Update availablegames.txt to remove the sold game
sed -i "/$game_name/d" "$available_games_file"
}




# Function to update gamescollection.txt after a game is bought
function update_collection {
local game_name=$1
local user_name="admin"  # Assuming user is admin
local collection_file="../test_data/gamescollection_test.txt"




# Add the game to the user's collection
echo "$game_name $user_name" >> "$collection_file"
}




# Create the output directory if it doesn't exist
mkdir -p "$output_dir"




# Perform daily login and actions
function perform_daily_operations {
local transaction_file=$(find_next_available_file $transaction_file_base)




# Redirect all output to the transaction file
exec 3>&1
exec 1>"$output_dir/$transaction_file" 2>&1




echo "Starting daily simulation..."




# Simulating sending input directly to the application
{
 echo "login"
 echo "nonadmin"
 echo "sell"
 echo "roblox"
 echo "20"




 echo "exit"
} | ../../src/distribution-system ../test_data/currentaccounts_test.txt ../test_data/availablegames_test.txt ../test_data/gamescollection_test.txt ../test_data/dailytransactions_test.txt




exec 1>&3




echo "Output written to $output_dir/$transaction_file"
}




# Example usage:
perform_daily_operations




echo "Daily processes completed successfully."