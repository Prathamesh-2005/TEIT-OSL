#!/bin/bash

FILE="address.txt"

if [ ! -f "$FILE" ]; then
  touch "$FILE"
fi

add_entry() {
  echo "Enter ID:"
  read id
  if grep -q "^$id;" "$FILE"; then
    echo "⚠️ ID already exists! Try again."
    return
  fi

  echo "Enter Name:"
  read name
  echo "Enter Phone Number:"
  read phone

  echo "$id;$name;$phone" >> "$FILE"
  echo "✅ Entry added successfully!"
}

search_entry() {
  echo "Enter Name or ID to search:"
  read search_term
  grep -i "$search_term" "$FILE" || echo "❌ No match found."
}

remove_entry() {
  read -p "Enter ID to delete: " id

  if ! grep -q "^$id;" "$FILE"; then
      echo "❌ ID $id not found."
      return
  fi

  sed -i "/^$id;/d" "$FILE"
  echo "🗑️ Entry with ID $id deleted successfully!"
}



display_entries() {
  echo "📘 Address Book:"
  echo "------------------------"
  if [ -s "$FILE" ]; then
      column -t -s ";" "$FILE"
  else
    echo "No entries yet."
  fi
  echo "------------------------"
}

while true; do
  echo ""
  echo "===== 📒 ADDRESS BOOK MENU ====="
  echo "1. Add Entry"
  echo "2. Search Entry"
  echo "3. Remove Entry"
  echo "4. Display All Entries"
  echo "5. Quit"
  echo "================================"
  echo "Enter your choice:"
  read choice

  case $choice in
    1) add_entry ;;
    2) search_entry ;;
    3) remove_entry ;;
    4) display_entries ;;
    5) echo "👋 Exiting..."; exit 0 ;;
    *) echo "Invalid choice! Try again." ;;
  esac
done