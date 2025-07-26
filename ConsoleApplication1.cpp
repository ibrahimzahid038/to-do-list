#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct Task {
    string name;
    string category;
    bool completed;

    string toString() const {
        return name + "," + category + "," + (completed ? "1" : "0");
    }

    static Task fromString(const string& line) {
        Task task;
        stringstream ss(line);
        getline(ss, task.name, ',');
        getline(ss, task.category, ',');
        string completedStr;
        getline(ss, completedStr, ',');
        task.completed = (completedStr == "1");
        return task;
    }
}; 
vector<Task> tasks; 
const string FILE_NAME = "tasks.txt";
 
void loadTasks() {
    ifstream file(FILE_NAME);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            tasks.push_back(Task::fromString(line));
        }
    }
    file.close();
} 
void saveTasks() {
    ofstream file(FILE_NAME);
    for (const Task& task : tasks) {
        file << task.toString() << endl;
    }
    file.close();
} 
void addTask() {
    Task task;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task.name);
    cout << "Enter task category (Work, Personal, etc.): ";
    getline(cin, task.category);
    task.completed = false;
    tasks.push_back(task);
    cout << "Task added.\n";
}
 
void viewTasks(bool completedOnly = false, const string& filterCategory = "") {
    cout << "\n--- Task List ---\n";
    int index = 1;
    for (const Task& task : tasks) {
        if ((completedOnly && !task.completed) || (!filterCategory.empty() && task.category != filterCategory)) {
            continue;
        }
        cout << setw(2) << index++ << ". " << task.name
            << " [" << task.category << "] "
            << (task.completed ? "(Completed)" : "(Pending)") << endl;
    }
    if (index == 1) cout << "No tasks to show.\n";
} 
void markCompleted() {
    viewTasks(false);
    cout << "Enter task number to mark as completed: ";
    int num;
    cin >> num;
    if (num > 0 && num <= tasks.size()) {
        tasks[num - 1].completed = true;
        cout << "Task marked as completed.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}
 
void removeTask() {
    viewTasks();
    cout << "Enter task number to remove: ";
    int num;
    cin >> num;
    if (num > 0 && num <= tasks.size()) {
        tasks.erase(tasks.begin() + num - 1);
        cout << "Task removed.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
} 
void filterByCategory() {
    string category;
    cout << "Enter category to filter: ";
    cin.ignore();
    getline(cin, category);
    viewTasks(false, category);
} 
void showMenu() {
    cout << "\n=== To-Do List Menu ===\n";
    cout << "1. Add Task\n";
    cout << "2. View All Tasks\n";
    cout << "3. View Completed Tasks\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. Remove Task\n";
    cout << "6. Filter by Category\n";
    cout << "7. Save and Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    loadTasks();
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: addTask(); break;
        case 2: viewTasks(); break;
        case 3: viewTasks(true); break;
        case 4: markCompleted(); break;
        case 5: removeTask(); break;
        case 6: filterByCategory(); break;
        case 7: saveTasks(); cout << "Tasks saved. Goodbye!\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
