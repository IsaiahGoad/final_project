#!/bin/bash

TARGET_DIR="."
mkdir -p "$TARGET_DIR"

# Array of filenames
FILES=("wiringx.h" "libwiringx.so")

# Array of URLs (order matters)
URLS=(
  "https://raw.githubusercontent.com/milkv-duo/duo-examples/main/include/system/wiringx.h"
  "https://raw.githubusercontent.com/milkv-duo/duo-examples/main/libs/system/musl_riscv64/libwiringx.so"
)

echo "Checking and downloading files..."

for i in "${!FILES[@]}"; do
  FILE_NAME="${FILES[$i]}"
  URL="${URLS[$i]}"
  DEST="$TARGET_DIR/$FILE_NAME"

  if [ -f "$DEST" ]; then
    echo "$FILE_NAME already exists, skipping."
  else
    echo "Downloading $FILE_NAME..."
    curl -L -o "$DEST" "$URL"
    
    if [ $? -ne 0 ]; then
      echo "Failed to download $FILE_NAME!"
      exit 1
    fi

    echo "$FILE_NAME downloaded."
  fi
done

echo "All done!"
