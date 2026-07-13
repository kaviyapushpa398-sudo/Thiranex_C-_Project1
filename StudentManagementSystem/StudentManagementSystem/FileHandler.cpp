#include "FileHandler.h"
#include <fstream>
#include <iostream>

// All student data lives in this text file, sitting alongside the
// executable. Change this path if you'd like the data stored elsewhere.
const std::string FileHandler::FILE_NAME = "students.txt";

void FileHandler::ensureFileExists() {
    // ios::app opens the file for appending, creating it if it does not
    // already exist, without erasing any existing content.
    std::ofstream file(FILE_NAME, std::ios::app);
    file.close();
}

std::vector<Student> FileHandler::loadAll() {
    std::vector<Student> students;
    std::ifstream file(FILE_NAME);
    std::string line;

    if (!file.is_open()) {
        return students; // empty list if file can't be opened
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromFileString(line));
        }
    }

    file.close();
    return students;
}

bool FileHandler::saveAll(const std::vector<Student>& students) {
    // ios::trunc wipes the existing file content so we can rewrite it
    // fresh with the updated list of records.
    std::ofstream file(FILE_NAME, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& s : students) {
        file << s.toFileString() << "\n";
    }

    file.close();
    return true;
}

bool FileHandler::addStudent(const Student& student) {
    // Appending directly is more efficient than rewriting the whole file.
    std::ofstream file(FILE_NAME, std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    file << student.toFileString() << "\n";
    file.close();
    return true;
}

bool FileHandler::idExists(int id) {
    std::vector<Student> students = loadAll();
    for (const auto& s : students) {
        if (s.getId() == id) {
            return true;
        }
    }
    return false;
}

bool FileHandler::searchById(int id, Student& result) {
    std::vector<Student> students = loadAll();
    for (const auto& s : students) {
        if (s.getId() == id) {
            result = s;
            return true;
        }
    }
    return false;
}

bool FileHandler::updateStudent(int id, const Student& updatedData) {
    std::vector<Student> students = loadAll();
    bool found = false;

    for (auto& s : students) {
        if (s.getId() == id) {
            s = updatedData;   // replace whole record (ID stays the same)
            s.setId(id);
            found = true;
            break;
        }
    }

    if (found) {
        saveAll(students); // persist the modified list back to disk
    }
    return found;
}

bool FileHandler::deleteStudent(int id) {
    std::vector<Student> students = loadAll();
    std::vector<Student> remaining;
    bool found = false;

    for (const auto& s : students) {
        if (s.getId() == id) {
            found = true; // skip adding this one -> effectively deletes it
        } else {
            remaining.push_back(s);
        }
    }

    if (found) {
        saveAll(remaining);
    }
    return found;
}

int FileHandler::countRecords() {
    return static_cast<int>(loadAll().size());
}
