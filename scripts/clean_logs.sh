#! /bin/sh

# Define the directory where we want to start searching for log files
search_dir="../src"

# Define the log file pattern
log_file_pattern="*.log"

# Find the log file (search for the most recently modified .log file)
log_file=$(find "$search_dir" -type f -name "$log_file_pattern" -not -path '*/ARCHIVE/*' -print0 | xargs -0 ls -t | head -n 1)

# Check if we found a log file
if [ -z "$log_file" ]; then
    echo "No log file found."
    exit 1
fi

# Extract the directory of the found log file
log_dir=$(dirname "$log_file")

# Create an archive directory inside the same directory as the log file
archive_dir="$log_dir/ARCHIVE"

# Create the archive directory if it doesn't exist
mkdir -p "$archive_dir"

# Extract the base file name (without the path)
base_filename=$(basename "$log_file")

# Create a new file name with a timestamp (for example, appending the date)
timestamp=$(date +"%Y%m%d_%H:%M:%S")
new_filename="${timestamp}_${base_filename}"

# Define the destination path (where the renamed file will be moved)
destination_path="$archive_dir/$new_filename"

# Rename and move the file
mv "$log_file" "$destination_path"

# Check if the move was successful
if [ $? -eq 0 ]; then
    echo "Log file successfully renamed and moved to: $destination_path"
else
    echo "Error renaming or moving the log file."
    exit 1
fi