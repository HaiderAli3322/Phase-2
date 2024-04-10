#!/bin/bash


# Define paths for input data
output_dir="daily_outputs"
merged_file="merged_daily_transactions.txt"


# Create or clear the merged file
> "$output_dir/$merged_file"


# Loop through the transaction files in order and concatenate them into one
for file in $(ls $output_dir/DailyTransactionFile*.txt | sort -V); do
   cat "$file" >> "$output_dir/$merged_file"
   echo "Merged $file"
done


echo "All transaction files have been merged into $output_dir/$merged_file."