#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

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

        std::cout << taskNumber << ". " << status << " " << task.description << " | Priority: " << task.priority << " | Due Date: " << dateStr << " | Category: " << task.category << std::endl;
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
        std::cout << "To-Do List CLI App" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Mark Task as Completed" << std::endl;
        std::cout << "3. List Tasks" << std::endl;
        std::cout << "4. List Tasks by Priority" << std::endl;
        std::cout << "5. List Tasks by Due Date" << std::endl;
        std::cout << "6. List Tasks by Category" << std::endl;
        std::cout << "7. Quit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string taskDescription;
                int taskPriority;
                time_t taskDueDate;
                std::string taskCategory;

                std::cout << "Enter task description: ";
                std::cin.ignore();  // Clear the newline character from the input buffer
                std::getline(std::cin, taskDescription);

                std::cout << "Enter task priority (1-5): ";
                std::cin >> taskPriority;

                std::cout << "Enter due date (YYYY-MM-DD): ";
                std::string dueDateStr;
                std::cin >> dueDateStr;
                struct tm tm;
                strptime(dueDateStr.c_str(), "%Y-%m-%d", &tm);
                taskDueDate = mktime(&tm);

                std::cout << "Enter task category: ";
                std::cin >> taskCategory;

                Task newTask;
                newTask.description = taskDescription;
                newTask.priority = taskPriority;
                newTask.dueDate = taskDueDate;
                newTask.category = taskCategory;
                newTask.completed = false;

                tasks.push_back(newTask);
                saveTasksToFile(tasks);  // Save tasks to file
                std::cout << "Task added!" << std::endl;
                break;
            }
            case 2: {
                int taskNumber;
                std::cout << "Enter task number to mark as completed: ";
                std::cin >> taskNumber;
                if (taskNumber >= 1 && taskNumber <= tasks.size()) {
                    tasks[taskNumber - 1].completed = true;
                    saveTasksToFile(tasks);  // Save tasks to file
                    std::cout << "Task marked as completed!" << std::endl;
                } else {
                    std::cout << "Invalid task number." << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Tasks:" << std::endl;
                printTasks(tasks);
                break;
            }
            case 4: {
                std::cout << "Tasks by Priority:" << std::endl;
                std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return a.priority < b.priority;
                });
                printTasks(tasks);
                break;
            }
            case 5: {
                std::cout << "Tasks by Due Date:" << std::endl;
                std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return a.dueDate < b.dueDate;
                });
                printTasks(tasks);
                break;
            }
            case 6: {
                std::string taskCategory;
                std::cout << "Enter category to list tasks: ";
                std::cin >> taskCategory;
                std::cout << "Tasks in Category: " << taskCategory << std::endl;
                for (const Task& task : tasks) {
                    if (task.category == taskCategory) {
                        std::string status = (task.completed) ? "[x]" : "[ ]";
                        struct tm* dueDate = localtime(&task.dueDate);
                        char dateStr[11];
                        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", dueDate);
                        std::cout << status << " " << task.description << " | Priority: " << task.priority << " | Due Date: " << dateStr << " | Category: " << task.category << std::endl;
                    }
                }
                break;
            }
            case 7:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }

    return 0;
}
