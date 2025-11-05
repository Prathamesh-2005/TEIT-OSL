#!/bin/bash

FILE="phonebook.txt"
[ ! -f "$FILE" ] && touch "$FILE"

add_entry() {
  read -p "Enter First Name: " fname
  read -p "Enter Last Name: " lname
  read -p "Enter Phone Number: " phone

  echo -e "${fname}\t${lname}\t${phone}" >> "$FILE"
  echo "✅ Entry added successfully!"
}

search_entry() {
  read -p "Enter Name or Phone Number to search: " term
  grep -i "$term" "$FILE" || echo "❌ No match found."
}

sort_by_lastname() {
  echo "📇 Phonebook sorted by Last Name:"
  sort -k2,2 "$FILE" | column -t
}

delete_entry() {
  read -p "Enter Phone Number to delete: " phone
  if grep -q "$phone" "$FILE"; then
    sed -i "/$phone/d" "$FILE"
    echo "🗑️ Entry deleted successfully!"
  else
    echo "❌ Phone number not found!"
  fi
}

display_all() {
  echo "📘 All Entries:"
  echo "-----------------------------"
  if [ -s "$FILE" ]; then
    column -t "$FILE"
  else
    echo "No entries found."
  fi
  echo "-----------------------------"
}

while true; do
  echo ""
  echo "===== 📞 PHONEBOOK MENU ====="
  echo "1. Add New Entry"
  echo "2. Search Entry"
  echo "3. Sort by Last Name"
  echo "4. Delete Entry"
  echo "5. Display All"
  echo "6. Quit"
  echo "============================="
  read -p "Enter your choice: " choice

  case $choice in
    1) add_entry ;;
    2) search_entry ;;
    3) sort_by_lastname ;;
    4) delete_entry ;;
    5) display_all ;;
    6) echo "👋 Exiting..."; exit ;;
    *) echo "Invalid choice! Try again." ;;
  esac
done
