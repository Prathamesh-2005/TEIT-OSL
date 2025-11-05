#!/bin/bash

FILE="address_book.txt"
[ ! -f "$FILE" ] && touch "$FILE"

add_entry() {
  read -p "Enter ID: " id
  if grep -q "^$id:" "$FILE"; then
    echo "⚠️ ID already exists!"
    return
  fi
  read -p "Enter Name: " name
  read -p "Enter Phone: " phone
  echo "$id:$name:$phone" >> "$FILE"
  echo "✅ Entry added!"
}

search_entry() {
  read -p "Enter Name or ID to search: " term
  echo "🔍 Search results:"
  grep -i "$term" "$FILE" | column -t -s ":" || echo "❌ No match found."
}

remove_entry() {
  read -p "Enter ID to delete: " id
  if grep -q "^$id:" "$FILE"; then
    sed -i "/^$id:/d" "$FILE"
    echo "🗑️ Entry deleted!"
  else
    echo "❌ ID not found!"
  fi
}

edit_entry() {
  read -p "Enter ID to edit: " id
  if ! grep -q "^$id:" "$FILE"; then
    echo "❌ ID not found!"
    return
  fi

  echo "Current record:"
  grep "^$id:" "$FILE" | column -t -s ":"

  read -p "Enter new Name: " new_name
  read -p "Enter new Phone: " new_phone

  sed -i "s/^$id:.*/$id:$new_name:$new_phone/" "$FILE"
  echo "✏️ Entry updated successfully!"
}

display_all() {
  echo "📘 Address Book:"
  echo "-------------------------"
  if [ -s "$FILE" ]; then
    column -t -s ":" "$FILE"
  else
    echo "No entries found."
  fi
  echo "-------------------------"
}

while true; do
  echo ""
  echo "===== 📒 ADDRESS BOOK MENU ====="
  echo "1. Add Entry"
  echo "2. Search Entry"
  echo "3. Remove Entry"
  echo "4. Edit Entry"
  echo "5. Display All"
  echo "6. Quit"
  echo "================================"
  read -p "Enter your choice: " choice

  case $choice in
    1) add_entry ;;
    2) search_entry ;;
    3) remove_entry ;;
    4) edit_entry ;;
    5) display_all ;;
    6) echo "👋 Exiting..."; exit ;;
    *) echo "Invalid choice! Try again." ;;
  esac
done
