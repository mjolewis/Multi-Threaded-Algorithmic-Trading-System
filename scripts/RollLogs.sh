#! /bin/sh

# A script that rolls log files every 24 hours
# Script is triggered by a cron

DATE=$(date +"%m-%d-%Y")
DIRNAME=ARCHIVE
#GZIP=gzip_${DATE}.tar.gz

# Create aliases for the source and destination directory
mkdir -p -- "$DIRNAME"
#SOURCE="/Users/mlewis/Downloads"
DESTINATION="./$(dirname ...){DIRNAME}"


#find . -name '*.log' -type f -exec mv -i '{}' ${DIRNAME}

find src -name '*.log' -not -path '*/archive/*' -type f -print0 | xargs -I '{}' mv "$(basename)${DATE}_{}" "${DESTINATION}"

#find . -name '*.log' > filename
#readlink -f filename

#-o -name '*.png' -print | grep Robert



# Move all files from the SOURCE created or modified in the last 24 hours into the DESTINATION
#find ${SOURCE} -mtime -1 -type f -print | xargs -I '{}' cp '{}' ${DESTINATION}

# Data compression
#tar -zcvf ${GZIP} ${DIRNAME}