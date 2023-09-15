#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> tasks;

void saveTasksToFile() {
    ofstream file("todolist.txt");
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.description << ',' << task.completed << '\n';
        }
        file.close();
    } else {
        cout << "Error: Could not save tasks to file." << endl;
    }
}

void loadTasksFromFile() {
    ifstream file("todolist.txt");
    tasks.clear();
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                Task task;
                task.description = line.substr(0, pos);
                task.completed = line.substr(pos + 1) == "1";
                tasks.push_back(task);
            }
        }
        file.close();
    } else {
        cout << "No existing tasks found." << endl;
    }
}

void displayTasks() {
    cout << "To-Do List:" << endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". ";
        if (tasks[i].completed) {
            cout << "[X] ";
        } else {
            cout << "[ ] ";
        }
        cout << tasks[i].description << endl;
    }
}

int main() {
    loadTasksFromFile();

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    Task task;
                    cout << "Enter task description: ";
                    cin.ignore();
                    getline(cin, task.description);
                    task.completed = false;
                    tasks.push_back(task);
                    saveTasksToFile();
                    break;
                }
            case 2:
                displayTasks();
                break;
            case 3:
                {
                    int taskIndex;
                    cout << "Enter task number to mark as completed: ";
                    cin >> taskIndex;
                    if (taskIndex >= 1 && taskIndex <= tasks.size()) {
                        tasks[taskIndex - 1].completed = true;
                        saveTasksToFile();
                    } else {
                        cout << "Invalid task number." << endl;
                    }
                    break;
                }
            case 4:
                {
                    int taskIndex;
                    cout << "Enter task number to delete: ";
                    cin >> taskIndex;
                    if (taskIndex >= 1 && taskIndex <= tasks.size()) {
                        tasks.erase(tasks.begin() + taskIndex - 1);
                        saveTasksToFile();
                    } else {
                        cout << "Invalid task number." << endl;
                    }
                    break;
                }
            case 5:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
