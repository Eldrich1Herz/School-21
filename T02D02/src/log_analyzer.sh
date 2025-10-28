#!/bin/bash
#created manually

#a log analysis script
log_file=$1  #the first argument passed to the script, representing the log file location

#basic checks for argument implementation
#the -z test checks if a string is empty
if [ -z "$log_file" ]; then
    echo "Usage: ./log_analyzer.sh path/to/logfile"
    exit 1
fi

#the -f test checks if the file exists
#the ! before the test inverts the logic, so the condition is true if the file does NOT exist
if [ ! -f "$log_file" ]; then
    echo "Error: File $log_file not found!"
    exit 1
fi

#analyze the log file and output three numbers:
#1.Total number of entries
#2.Number of unique files  
#3.Number of hash changes
total_entries=$(wc -l < "$log_file" | tr -d ' ')

#count number of unique files in the log
#awk '{print $1}' extracts just the filenames (first column)
#sort arranges the filenames in order for uniq to work properly  
#uniq removes duplicate filenames, keeping only unique ones
#wc -l counts how many unique files remain
unique_files=$(awk '{print $1}' "$log_file" | sort | uniq | wc -l | tr -d ' ')

#count number of hash changes in the log
#this awk script tracks when the same file has different hashes between entries
#prev_file && prev_file == $1 - checks if we're looking at the same file as previous line
#prev_hash != $2 - checks if the hash changed from previous entry
#{count++} - increments our counter when both conditions are true
#{prev_file=$1; prev_hash=$2} - remembers current file/hash for next comparison
#END {print count+0} - prints final count (count+0 ensures we get 0 if no changes)
hash_changes=$(awk 'prev_file && prev_file == $1 && prev_hash != $2 {count++} {prev_file=$1; prev_hash=$2} END {print count+0}' "$log_file")

#output the three statistics as space-separated numbers
echo "$total_entries $unique_files $hash_changes"
