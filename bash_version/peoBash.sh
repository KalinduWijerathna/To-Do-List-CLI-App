#!/bin/bash

# Initialize an empty to-do list
tasks=()

# Function to print the to-do list
print_tasks() {
  if [[ ${#tasks[@]} -eq 0 ]]; then
    echo "No tasks found."
  else
    echo "Tasks:"
    for i in "${!tasks[@]}"; do
      echo "${i+1}. ${tasks[$i]}"
    done
  fi
}

# Function to add a task to the to-do list
add_task() {
  if [[ -z "$1" ]]; then
    echo "Task cannot be empty."
    return
  fi
  tasks+=("$1")
  echo "Task added."
}

# Function to remove a task from the to-do list
remove_task() {
  if [[ ${#tasks[@]} -eq 0 ]]; then
    echo "No tasks found."
    return
  fi
  if [[ -z "$1" ]] || (( $1 -gt ${#tasks[@]} )) || (( $1 -lt 1 )); then
    echo "Invalid task number."
    return
  fi
  unset tasks[$(( $1 - 1 ))]
  tasks=("${tasks[@]}")
  echo "Task removed."
}

# Main loop
while true; do
  clear
  echo -e "\e[93m██╗    ██╗ ██████╗ ██╗   ██╗███████╗██████╗  \e[0m"
  echo -e "\e[93m██║    ██║██╔═══██╗██║   ██║██╔════╝██╔══██╗ \e[0m"
  echo -e "\e[93m██║ █╗ ██║██║   ██║██║   ██║█████╗  ██████╔╝ \e[0m"
  echo -e "\e[93m██║███╗██║██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗ \e[0m"
  echo -e "\e[93md█╚███╔╝██║╚██████╔╝ ╚████╔╝ ███████╗██║  ██║ \e[0m"
  echo -e "\e[93md██║  ██╗╚═════╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝ \e[0m"
  echo ""
  echo -e "\e[93mA simple to-do list CLI.\e[0m"
  echo ""
  echo "1. Add task"
  echo "2. Remove task"
  echo "3. Print tasks"
  echo "4. Quit"
  echo ""
  echo -e "\e[93mEnter your choice: \e[0m"
  read choice
  case $choice in
    1)
      echo -e "\e[93mEnter task: \e[0m"
      read task
      add_task "$task"
      ;;
    2)
      echo -e "\e[93mEnter task number to remove: \e[0m"
      read number
      remove_task "$number"
      ;;
    3)
      print_tasks
      read -n 1 -s -r -p "Press any key to continue..."
      ;;
    4)
      break
      ;;
    *)
      echo -e "\e[91mInvalid choice. Try again.\e[0m"
      read -n 1 -s -r -p "Press any key to continue..."
      ;;
  esac
done
