#include "Student.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// ---------- Constructors ----------

Student::Student()
    : id(0), name(""), age(0), gender(""), department(""),
      yearSemester(""), phone(""), email(""), marks(0.0) {}

Student::Student(int id, const std::string& name, int age, const std::string& gender,
                  const std::string& department, const std::string& yearSemester,
                  const std::string& phone, const std::string& email, double marks)
    : id(id), name(name), age(age), gender(gender), department(department),
      yearSemester(yearSemester), phone(phone), email(email), marks(marks) {}

// ---------- Getters ----------

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
int Student::getAge() const { return age; }
std::string Student::getGender() const { return gender; }
std::string Student::getDepartment() const { return department; }
std::string Student::getYearSemester() const { return yearSemester; }
std::string Student::getPhone() const { return phone; }
std::string Student::getEmail() const { return email; }
double Student::getMarks() const { return marks; }

// ---------- Setters ----------

void Student::setId(int newId) { id = newId; }
void Student::setName(const std::string& newName) { name = newName; }
void Student::setAge(int newAge) { age = newAge; }
void Student::setGender(const std::string& newGender) { gender = newGender; }
void Student::setDepartment(const std::string& newDepartment) { department = newDepartment; }
void Student::setYearSemester(const std::string& newYearSemester) { yearSemester = newYearSemester; }
void Student::setPhone(const std::string& newPhone) { phone = newPhone; }
void Student::setEmail(const std::string& newEmail) { email = newEmail; }
void Student::setMarks(double newMarks) { marks = newMarks; }

// ---------- File Serialization ----------

// Combines every field into one line, separated by FIELD_DELIMITER.
// Example:  101|John Doe|20|Male|Computer Science|3rd Year|9876543210|john@mail.com|85.50
std::string Student::toFileString() const {
    std::ostringstream oss;
    oss << id            << FIELD_DELIMITER
        << name          << FIELD_DELIMITER
        << age            << FIELD_DELIMITER
        << gender         << FIELD_DELIMITER
        << department     << FIELD_DELIMITER
        << yearSemester   << FIELD_DELIMITER
        << phone          << FIELD_DELIMITER
        << email          << FIELD_DELIMITER
        << marks;
    return oss.str();
}

// Splits a delimited line back into its individual fields and builds
// a Student object from them.
Student Student::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::string fields[9];
    int index = 0;

    // getline with a custom delimiter pulls out one field at a time.
    while (std::getline(ss, token, FIELD_DELIMITER) && index < 9) {
        fields[index++] = token;
    }

    Student s;
    s.id           = fields[0].empty() ? 0 : std::stoi(fields[0]);
    s.name         = fields[1];
    s.age          = fields[2].empty() ? 0 : std::stoi(fields[2]);
    s.gender       = fields[3];
    s.department   = fields[4];
    s.yearSemester = fields[5];
    s.phone        = fields[6];
    s.email        = fields[7];
    s.marks        = fields[8].empty() ? 0.0 : std::stod(fields[8]);
    return s;
}

// ---------- Display Helpers ----------

void Student::displayHeader() {
    std::cout << std::left
               << std::setw(6)  << "ID"
               << std::setw(20) << "Name"
               << std::setw(5)  << "Age"
               << std::setw(8)  << "Gender"
               << std::setw(18) << "Department"
               << std::setw(12) << "Year/Sem"
               << std::setw(14) << "Phone"
               << std::setw(25) << "Email"
               << std::setw(8)  << "Marks"
               << std::endl;
    std::cout << std::string(116, '-') << std::endl;
}

void Student::displayRow() const {
    std::cout << std::left
               << std::setw(6)  << id
               << std::setw(20) << name
               << std::setw(5)  << age
               << std::setw(8)  << gender
               << std::setw(18) << department
               << std::setw(12) << yearSemester
               << std::setw(14) << phone
               << std::setw(25) << email
               << std::setw(8)  << std::fixed << std::setprecision(2) << marks
               << std::endl;
}

void Student::displayDetailed() const {
    std::cout << "\n--------------------------------------------\n";
    std::cout << " Student ID     : " << id << "\n";
    std::cout << " Name           : " << name << "\n";
    std::cout << " Age            : " << age << "\n";
    std::cout << " Gender         : " << gender << "\n";
    std::cout << " Department     : " << department << "\n";
    std::cout << " Year/Semester  : " << yearSemester << "\n";
    std::cout << " Phone Number   : " << phone << "\n";
    std::cout << " Email Address  : " << email << "\n";
    std::cout << " Marks          : " << std::fixed << std::setprecision(2) << marks << "\n";
    std::cout << "--------------------------------------------\n";
}
