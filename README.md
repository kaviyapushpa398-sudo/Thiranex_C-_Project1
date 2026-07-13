# Thiranex_C-_Project1

# 🎓 Student Management System

A **Console-Based Student Management System** developed in **C++** using **Object-Oriented Programming (OOP)** and **File Handling**. This application allows users to efficiently manage student records through a simple menu-driven interface while ensuring data is stored permanently using files.

---

## 📖 About the Project

The **Student Management System** is a beginner-friendly C++ application designed to manage student information. It demonstrates the use of classes, objects, file handling, functions, and menu-driven programming to perform various operations on student records.

The application stores all student data in a file, allowing information to persist even after the program is closed.

---

## ✨ Features

- ➕ Add New Student
- 📋 Display All Students
- 🔍 Search Student by ID
- ✏️ Update Student Details
- ❌ Delete Student Record
- 💾 Permanent Data Storage using File Handling
- 📂 Menu-Driven Console Interface
- 🛡️ Duplicate Student ID Validation
- ⚠️ Error Handling and Input Validation

---

## 🛠️ Technologies Used

| Technology | Description |
|------------|-------------|
| 💻 Language | C++ |
| 📂 File Handling | fstream |
| 🧱 Programming Paradigm | Object-Oriented Programming (OOP) |
| 🖥️ IDE | Visual Studio Code / Code::Blocks / Dev-C++ |
| ⚙️ Compiler | g++ (MinGW/MSYS2) |

---

## 📁 Project Structure

```text
StudentManagementSystem/
│
├── main.cpp
├── Student.cpp
├── Student.h
├── FileHandler.cpp
├── FileHandler.h
├── students.txt
└── README.md
```

---

## 🚀 Functionalities

### ➕ Add Student
- Add a new student record.
- Store the record permanently in a file.

### 📋 Display Students
- View all stored student records.

### 🔍 Search Student
- Search student information using Student ID.

### ✏️ Update Student
- Modify existing student details.

### ❌ Delete Student
- Remove a student record permanently.

### 🚪 Exit
- Safely close the application.

---

## 📚 Student Information Stored

Each student record contains:

- 🆔 Student ID
- 👤 Full Name
- 🎂 Age
- 🚻 Gender
- 🏫 Department
- 📖 Year/Semester
- 📱 Phone Number
- 📧 Email Address
- 📊 Marks

---

## 💾 File Handling

The application uses the C++ **fstream** library to:

- Read student records
- Write new records
- Update existing records
- Delete records
- Store data permanently

---

## ▶️ How to Compile

Open the terminal inside the project folder and run:

```bash
g++ main.cpp Student.cpp FileHandler.cpp -o StudentManagementSystem.exe
```

---

## ▶️ How to Run

Windows

```bash
.\StudentManagementSystem.exe
```

Linux/macOS

```bash
./StudentManagementSystem
```

---

## 🖥️ Sample Menu

```text
===============================
    STUDENT MANAGEMENT SYSTEM
===============================

1. Add Student
2. Display Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit

Enter Your Choice:
```

---

## 🎯 Learning Outcomes

Through this project, you will gain practical experience in:

- Object-Oriented Programming
- Classes and Objects
- Functions
- File Handling
- Menu-Driven Programming
- Data Management
- Input Validation
- Problem Solving
- Console Application Development

---

## 🔮 Future Enhancements

- 🔐 Admin Login System
- 📅 Attendance Management
- 📝 Grade Calculation
- 📄 Report Card Generation
- 📊 Student Performance Analysis
- 📥 Import/Export Student Data
- 🌐 GUI Version using Qt or C++

---

## 👩‍💻 Author

**Kaviya B**

🎓 B.Sc. Computer Science

💻 C++ Programming Internship Project

---

## 📜 License

This project is developed for **educational and internship purposes**. It is free to use, modify, and distribute for learning and academic projects.

---

## ⭐ Acknowledgement

Special thanks to **Thiranex** for providing this internship opportunity and encouraging practical learning through real-world C++ projects.
