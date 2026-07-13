#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// Delimiter used to separate fields when a Student record is saved to
// or loaded from the file. Using a rare character avoids clashes with
// commas that might appear inside names or addresses.
const char FIELD_DELIMITER = '|';

/*
 * Student
 * --------
 * Represents a single student record and encapsulates all data
 * (attributes) and behavior (getters/setters + file (de)serialization)
 * related to a student.
 */
class Student {
private:
    int         id;
    std::string name;
    int         age;
    std::string gender;      // "Male", "Female", "Other"
    std::string department;
    std::string yearSemester;
    std::string phone;
    std::string email;
    double      marks;

public:
    // Constructors
    Student();
    Student(int id, const std::string& name, int age, const std::string& gender,
            const std::string& department, const std::string& yearSemester,
            const std::string& phone, const std::string& email, double marks);

    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getDepartment() const;
    std::string getYearSemester() const;
    std::string getPhone() const;
    std::string getEmail() const;
    double getMarks() const;

    // Setters
    void setId(int newId);
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setGender(const std::string& newGender);
    void setDepartment(const std::string& newDepartment);
    void setYearSemester(const std::string& newYearSemester);
    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);
    void setMarks(double newMarks);

    // Converts this Student object into a single delimited line of text
    // suitable for writing to the data file.
    std::string toFileString() const;

    // Builds and returns a Student object by parsing a delimited line of
    // text that was previously produced by toFileString().
    static Student fromFileString(const std::string& line);

    // Prints a nicely formatted, tabular representation of this student's
    // details to the console. Pass showHeader=true once at the top of a
    // table to print column titles first.
    static void displayHeader();
    void displayRow() const;
    void displayDetailed() const;
};

#endif // STUDENT_H
