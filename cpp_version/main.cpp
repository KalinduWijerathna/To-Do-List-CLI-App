#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ncurses.h> // to open a text based ui 


struct Task {
    std::string description;
    bool completed;
    int priority;
    time_t dueDate;
    std::string category;
};

void printTasks(const std::vector<Task>& tasks) {
    int taskNumber = 1;
    for (const Task& task : tasks) {
        std::string status = (task.completed) ? "[x]" : "[ ]";
        struct tm* dueDate = localtime(&task.dueDate);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", dueDate);

        //std::cout << taskNumber << ". " << status << " " << task.description << " | Priority: " << task.priority << " | Due Date: " << dateStr << " | Category: " << task.category << std::endl;
        
        // Set text color
        attron(COLOR_PAIR(1)); //  initialized color pair 1 for green text
        printw("%d. %s %s | Priority: %d | Due Date: %s | Category: %s\n", taskNumber, status.c_str(), task.description.c_str(), task.priority, dateStr, task.category.c_str());
	attroff(COLOR_PAIR(1)); // turn off color attribute
        taskNumber++;
    }
}

void saveTasksToFile(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    if (file.is_open()) {
        for (const Task& task : tasks) {
            if (!task.completed) {
                file << task.description << "\n";
                file << task.priority << "\n";
                file << task.dueDate << "\n";
                file << task.category << "\n";
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to save tasks to file." << std::endl;
    }
}

int main() {

    // Initialize ncurses
    initscr();
    start_color(); // enable color output
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // create color pair 1 (green text on black background)
    //raw();
    //keypad(stdscr, TRUE);
    //noecho();
    
    std::vector<Task> tasks;

    // Load existing tasks from "tasks.txt" file
    std::ifstream file("tasks.txt");
    if (file.is_open()) {
        std::string taskDescription;
        int taskPriority;
        time_t taskDueDate;
        std::string taskCategory;
        while (std::getline(file, taskDescription)) {
            Task task;
            task.description = taskDescription;
            file >> taskPriority;
            file.ignore(); // Clear newline character
            task.priority = taskPriority;
            file >> taskDueDate;
            file.ignore(); // Clear newline character
            task.dueDate = taskDueDate;
            std::getline(file, taskCategory);
            task.category = taskCategory;
            task.completed = false;
            tasks.push_back(task);
        }
        file.close();
    }

    while (true) {
    
        clear(); // Clear screen before printing menu
        
        // Print menu options
        printw("To-Do List CLI App\n");
        printw("1. Add Task\n");
        printw("2. Mark Task as Completed\n");
        printw("3. List Tasks\n");
        printw("4. List Tasks by Priority\n");
        printw("5. List Tasks by Due Date\n");
        printw("6. List Tasks by Category\n");
        printw("7. Quit\n");
        printw("Enter your choice: ");
        
        //std::cout << "To-Do List CLI App" << std::endl;
        //std::cout << "1. Add Task" << std::endl;
        //std::cout << "2. Mark Task as Completed" << std::endl;
        //std::cout << "3. List Tasks" << std::endl;
        //std::cout << "4. List Tasks by Priority" << std::endl;
        //std::cout << "5. List Tasks by Due Date" << std::endl;
        //std::cout << "6. List Tasks by Category" << std::endl;
        //std::cout << "7. Quit" << std::endl;
        //std::cout << "Enter your choice: ";

        int choice;
        scanw("%d", &choice);
        //std::cin >> choice;

        
switch (choice) {

    case 1: {

        std::string taskDescription;

        int taskPriority;

        time_t taskDueDate;

        std::string taskCategory;


        printw("Enter task description: ");

        refresh(); // Refresh screen after printing

        char taskDescriptionStr[256];

        scanw(" %255[^\n]", taskDescriptionStr); // Read up to 255 characters or until a newline character is encountered

        taskDescription = taskDescriptionStr;


        printw("Enter task priority (1-5): ");

        refresh(); // Refresh screen after printing

        scanw("%d", &taskPriority);


        printw("Enter due date (YYYY-MM-DD): ");

        refresh(); // Refresh screen after printing

        char dueDateStr[11];

        scanw(" %10s", dueDateStr); // Read exactly 10 characters

        struct tm tm;

        strptime(dueDateStr, "%Y-%m-%d", &tm);

        taskDueDate = mktime(&tm);


        printw("Enter task category: ");

        refresh(); // Refresh screen after printing

        char taskCategoryStr[256];

        scanw(" %255[^\n]", taskCategoryStr); // Read up to 255 characters or until a newline character is encountered

        taskCategory = taskCategoryStr;


        Task newTask;

        newTask.description = taskDescription;

        newTask.priority = taskPriority;

        newTask.dueDate = taskDueDate;

        newTask.category = taskCategory;

        newTask.completed = false;


        tasks.push_back(newTask);

        saveTasksToFile(tasks);  // Save tasks to file

        printw("Task added!\n");

        refresh(); // Refresh screen after printing

        break;

    }

    case 2: {

        int taskNumber;

        printw("Enter task number to mark as completed: ");

        refresh(); // Refresh screen after printing

        scanw("%d", &taskNumber);

        if (taskNumber >= 1 && taskNumber <= tasks.size()) {

            tasks[taskNumber - 1].completed = true;

            saveTasksToFile(tasks);  // Save tasks to file

            printw("Task marked as completed!\n");

            refresh(); // Refresh screen after printing

        } else {

            printw("Invalid task number.\n");

            refresh(); // Refresh screen after printing

        }

        break;

    }

    case 3: {

        printw("Tasks:\n");

        refresh(); // Refresh screen after printing

        printTasks(tasks);

        break;

    }

    case 4: {

        printw("Tasks by Priority:\n");

        refresh(); // Refresh screen after printing

        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {

            return a.priority < b.priority;

        });

        printTasks(tasks);

        break;

    }

    case 5: {

        printw("Tasks by Due Date:\n");

        refresh(); // Refresh screen after printing

        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {

            return a.dueDate < b.dueDate;

        });

        printTasks(tasks);

        break;

    }

    case 6: {

        std::string taskCategory;

        printw("Enter category to list tasks: ");

        refresh(); // Refresh screen after printing

        char taskCategoryStr[256];

        scanw(" %255[^\n]", taskCategoryStr); // Read up to 255 characters or until a newline character is encountered

        taskCategory = taskCategoryStr;

        printw("Tasks in Category: %s\n", taskCategory.c_str());

        refresh(); // Refresh screen after printing

        for (const Task& task : tasks) {

            if (task.category == taskCategory) {

                std::string status = (task.completed)? "[x]" : "[ ]";

                struct tm* dueDate = localtime(&task.dueDate);

                char dateStr[11];

                strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", dueDate);

                printw("%s %s | Priority: %d | Due Date: %s | Category: %s\n", status.c_str(), task.description.c_str(), task.priority, dateStr, task.category.c_str());

                refresh(); // Refresh screen after printing

            }

        }

        break;

    }

    case 7:

        endwin(); // End ncurses

        printw("Goodbye For Now!\n");

        refresh(); // Refresh screen after printing

        return 0;

    default:

        printw("Invalid choice.\n");

        refresh(); // Refresh screen after printing

}
}
    endwin(); // end ncurses
    return 0;
}
