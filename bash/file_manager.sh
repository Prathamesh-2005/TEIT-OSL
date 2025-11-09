#!/bin/bash

check_file()
{
    read -p "enter file name to check: " file
    if [ -f "$file" ]; then
     echo "File '$file' exits"
    else 
     echo "File '$file'  does not exist"
     fi
}

read_file()
{
    read -p "Enter filename to read: " file
    if [ -f "$file" ]; then 
    echo "Contents of '$file' :"
    echo "----------"
     cat "$file"
     echo "----------"
    else 
     echo " file not found"
    fi
}

delete_file()
{
    read -p "Enter name of file "
    if [ -f "$file" ]; then
     rm "$file"
     echo "file '$file' deleted "
    else echo "file not found"
   fi 
}

list_files()
{
    echo "files in directory are :"
    echo "-----------"
    ls -l 
    echo "-----------"
}

while true; do 
    echo ""
  echo "===== 📂 FILE MANAGEMENT MENU ====="
  echo "1. Test if file exists"
  echo "2. Read a file"
  echo "3. Delete a file"
  echo "4. Display list of files"
  echo "5. Exit"
  echo "==================================="
  read -p "Enter your choice [1-5]: " choice

  case $choice in 
  1) check_file ;;
  2) read_file ;;
  3) delete_file ;;
  4) list_files ;;
  5) echo "exiting......"; exit 0 ;;
  *) echo "Invalid choice ";;
  esac
done