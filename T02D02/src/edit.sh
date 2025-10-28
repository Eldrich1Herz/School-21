#!/bin/bash

# Check for exactly 3 arguments
if [ $# -ne 3 ]; then
    echo "Usage: ./edit.sh filename 'old text' 'new text'"
    exit 1
fi

file="$1" # filename
search="$2" # text to replace
replace="$3" # new text

# Get absolute path with fallback
if ! abs_file=$(realpath "$file" 2>/dev/null); then
    if [[ "$file" == /* ]]; then
        abs_file="$file"
    else
        abs_file="$PWD/$file"
    fi
fi

# Check if file exists
if [ ! -f "$abs_file" ]; then
    echo "Error: File $file not found!"
    exit 1
fi

# Perform text replacement
sed -i '' "s|$search|$replace|g" "$abs_file"

# Log changes in the required format
size=$(wc -c < "$abs_file" | xargs)
sha=$(shasum -a 256 "$abs_file" | cut -d' ' -f1)
echo "${file#./} - $size - $(date '+%Y-%m-%d %H:%M:%S') - $sha - sha256" >> ./src/files.log

echo "Done! Changed '$search' to '$replace' in $file"