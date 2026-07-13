/*
 * ===========================================================
 *  Console-Based Student Management System
 *  -----------------------------------------
 *  A menu-driven C++ application demonstrating Object-Oriented
 *  Programming (classes/objects) and File Handling (fstream).
 *
 *  Features:
 *    1. Add a new student
 *    2. Display all student records
 *    3. Search a student by ID
 *    4. Update existing student details
 *    5. Delete a student record
 *    6. Exit
 *
 *  Records are stored permanently in students.txt so data
 *  survives between program runs.
 * ===========================================================
 */

#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include "Student.h"
#include "FileHandler.h"

using namespace std;

// ----------------------------------------------------------------
// Input-validation helper functions
// ----------------------------------------------------------------

// Reads an integer safely, re-prompting on invalid (non-numeric) input.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // reset error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "  [!] Invalid input. Please enter a whole number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard trailing newline
            return value;
        }
    }
}

// Reads an integer constrained to [minVal, maxVal].
int readIntInRange(const string& prompt, int minVal, int maxVal) {
    while (true) {
        int value = readInt(prompt);
        if (value < minVal || value > maxVal) {
            cout << "  [!] Please enter a value between " << minVal << " and " << maxVal << ".\n";
        } else {
            return value;
        }
    }
}

// Reads a double safely (used for marks), re-prompting on invalid input.
double readDoubleInRange(const string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (value < minVal || value > maxVal) {
            cout << "  [!] Please enter a value between " << minVal << " and " << maxVal << ".\n";
        } else {
            return value;
        }
    }
}

// Reads a full line of text and keeps prompting until it is non-empty.
string readNonEmptyLine(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (line.empty()) {
            cout << "  [!] This field cannot be empty. Please try again.\n";
        } else {
            return line;
        }
    }
}

// Reads a gender value restricted to Male / Female / Other.
string readGender() {
    while (true) {
        cout << "Enter Gender (M/F/O): ";
        string input;
        getline(cin, input);
        if (!input.empty()) {
            char c = toupper(input[0]);
            if (c == 'M') return "Male";
            if (c == 'F') return "Female";
            if (c == 'O') return "Other";
        }
        cout << "  [!] Please enter M, F, or O.\n";
    }
}

// Reads a phone number, validating that it contains only digits and
// is a reasonable length (7-15 digits, covers most real-world formats).
string readPhone() {
    while (true) {
        cout << "Enter Phone Number (digits only): ";
        string input;
        getline(cin, input);
        bool valid = !input.empty() && input.size() >= 7 && input.size() <= 15;
        if (valid) {
            for (char c : input) {
                if (!isdigit(static_cast<unsigned char>(c))) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) return input;
        cout << "  [!] Please enter a valid phone number (7-15 digits, numbers only).\n";
    }
}

// Reads an email address, doing a light-weight sanity check for
// the presence of '@' and '.' in a reasonable arrangement.
string readEmail() {
    while (true) {
        cout << "Enter Email Address: ";
        string input;
        getline(cin, input);
        size_t atPos = input.find('@');
        size_t dotPos = input.find_last_of('.');
        bool valid = (atPos != string::npos) && (dotPos != string::npos) &&
                     (atPos > 0) && (dotPos > atPos + 1) && (dotPos < input.size() - 1);
        if (valid) return input;
        cout << "  [!] Please enter a valid email address (e.g. name@example.com).\n";
    }
}

// ----------------------------------------------------------------
// Menu operations
// ----------------------------------------------------------------

void pauseForUser() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void addStudent() {
    cout << "\n===== Add New Student =====\n";

    int id = readInt("Enter Student ID: ");

    if (FileHandler::idExists(id)) {
        cout << "  [X] A student with ID " << id << " already exists. Duplicate IDs are not allowed.\n";
        pauseForUser();
        return;
    }

    string name = readNonEmptyLine("Enter Full Name: ");
    int age = readIntInRange("Enter Age: ", 1, 120);
    string gender = readGender();
    string department = readNonEmptyLine("Enter Department: ");
    string yearSem = readNonEmptyLine("Enter Year/Semester (e.g. 2nd Year / Sem 4): ");
    string phone = readPhone();
    string email = readEmail();
    double marks = readDoubleInRange("Enter Marks (0-100): ", 0.0, 100.0);

    Student newStudent(id, name, age, gender, department, yearSem, phone, email, marks);

    if (FileHandler::addStudent(newStudent)) {
        cout << "\n  [OK] Student record added successfully!\n";
    } else {
        cout << "\n  [X] Failed to write to the data file.\n";
    }
    pauseForUser();
}

void displayAllStudents() {
    cout << "\n===== All Student Records =====\n";
    vector<Student> students = FileHandler::loadAll();

    if (students.empty()) {
        cout << "  No student records found.\n";
    } else {
        Student::displayHeader();
        for (const auto& s : students) {
            s.displayRow();
        }
        cout << "\nTotal Records: " << students.size() << "\n";
    }
    pauseForUser();
}

void searchStudent() {
    cout << "\n===== Search Student =====\n";
    int id = readInt("Enter Student ID to search: ");

    Student result;
    if (FileHandler::searchById(id, result)) {
        cout << "\n  [OK] Student found:\n";
        result.displayDetailed();
    } else {
        cout << "\n  [X] No student found with ID " << id << ".\n";
    }
    pauseForUser();
}

void updateStudent() {
    cout << "\n===== Update Student =====\n";
    int id = readInt("Enter Student ID to update: ");

    Student existing;
    if (!FileHandler::searchById(id, existing)) {
        cout << "\n  [X] No student found with ID " << id << ". Nothing to update.\n";
        pauseForUser();
        return;
    }

    cout << "\nCurrent details:\n";
    existing.displayDetailed();

    cout << "\nEnter new details below (Student ID cannot be changed).\n";
    string name = readNonEmptyLine("Enter Full Name: ");
    int age = readIntInRange("Enter Age: ", 1, 120);
    string gender = readGender();
    string department = readNonEmptyLine("Enter Department: ");
    string yearSem = readNonEmptyLine("Enter Year/Semester: ");
    string phone = readPhone();
    string email = readEmail();
    double marks = readDoubleInRange("Enter Marks (0-100): ", 0.0, 100.0);

    Student updated(id, name, age, gender, department, yearSem, phone, email, marks);

    if (FileHandler::updateStudent(id, updated)) {
        cout << "\n  [OK] Student record updated successfully!\n";
    } else {
        cout << "\n  [X] Update failed unexpectedly.\n";
    }
    pauseForUser();
}

void deleteStudent() {
    cout << "\n===== Delete Student =====\n";
    int id = readInt("Enter Student ID to delete: ");

    Student existing;
    if (!FileHandler::searchById(id, existing)) {
        cout << "\n  [X] No student found with ID " << id << ".\n";
        pauseForUser();
        return;
    }

    cout << "\nRecord to be deleted:\n";
    existing.displayDetailed();

    cout << "\nAre you sure you want to delete this record? (y/n): ";
    string confirm;
    getline(cin, confirm);

    if (!confirm.empty() && (confirm[0] == 'y' || confirm[0] == 'Y')) {
        if (FileHandler::deleteStudent(id)) {
            cout << "\n  [OK] Student record deleted successfully!\n";
        } else {
            cout << "\n  [X] Deletion failed unexpectedly.\n";
        }
    } else {
        cout << "\n  Deletion cancelled.\n";
    }
    pauseForUser();
}

void printMenu() {
    cout << "\n============================================\n";
    cout << "     STUDENT MANAGEMENT SYSTEM (C++)\n";
    cout << "============================================\n";
    cout << " Total Records: " << FileHandler::countRecords() << "\n";
    cout << "--------------------------------------------\n";
    cout << " 1. Add a new student\n";
    cout << " 2. Display all student records\n";
    cout << " 3. Search a student by ID\n";
    cout << " 4. Update existing student details\n";
    cout << " 5. Delete a student record\n";
    cout << " 6. Exit\n";
    cout << "============================================\n";
}

int main() {
    // Make sure the data file exists before we start using it.
    FileHandler::ensureFileExists();

    cout << "Welcome to the Student Management System!\n";
    cout << "Data is stored permanently in 'students.txt'.\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readIntInRange("Enter your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                cout << "\nThank you for using the Student Management System. Goodbye!\n";
                running = false;
                break;
        }
    }

    return 0;
}
