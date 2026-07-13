#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "Student.h"

/*
 * FileHandler
 * -----------
 * Wraps every interaction with the students data file (students.txt)
 * so that the rest of the program never has to deal with fstream
 * directly. All methods are static because FileHandler holds no
 * per-object state -- it just operates on the one data file.
 */
class FileHandler {
private:
    static const std::string FILE_NAME; // path to the data file

public:
    // Makes sure the data file exists; creates an empty one if it
    // doesn't (so the very first run of the program doesn't crash).
    static void ensureFileExists();

    // Reads every record from the file into memory.
    static std::vector<Student> loadAll();

    // Overwrites the file with the given list of records. Used after
    // updates/deletes to persist the modified in-memory list.
    static bool saveAll(const std::vector<Student>& students);

    // Appends one new student record to the end of the file.
    static bool addStudent(const Student& student);

    // Returns true if a student with the given ID already exists.
    static bool idExists(int id);

    // Searches for a student by ID. Returns true and fills 'result' if
    // found, otherwise returns false.
    static bool searchById(int id, Student& result);

    // Updates an existing student record (matched by ID) with new data.
    // Returns true if the record was found and updated.
    static bool updateStudent(int id, const Student& updatedData);

    // Deletes the student record with the given ID.
    // Returns true if the record was found and deleted.
    static bool deleteStudent(int id);

    // Returns how many student records are currently stored.
    static int countRecords();
};

#endif // FILE_HANDLER_H
