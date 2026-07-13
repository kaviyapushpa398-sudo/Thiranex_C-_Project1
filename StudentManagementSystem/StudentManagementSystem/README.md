# Console-Based Student Management System (C++)

A menu-driven **Student Management System** built in **C++** using
**Object-Oriented Programming** (classes & objects) and **File Handling**
(`fstream`). Student records are stored permanently in a text file
(`students.txt`), so data is retained even after the program is closed.

Ideal for coursework, practice projects, or an internship / academic submission.

---

## Features

| # | Feature                              | Description                                                   |
|---|---------------------------------------|-----------------------------------------------------------------|
| 1 | Add a new student                     | Prompts for all details, validates input, prevents duplicate IDs |
| 2 | Display all student records           | Shows a formatted table of every student on file                |
| 3 | Search a student by Student ID        | Displays full details of a matching student                     |
| 4 | Update existing student details       | Loads current details and lets you overwrite them               |
| 5 | Delete a student record                | Confirms before permanently removing a record                    |
| 6 | Exit                                   | Safely exits the application                                    |

Each student record contains:
- Student ID
- Full Name
- Age
- Gender
- Department
- Year / Semester
- Phone Number
- Email Address
- Marks

**Input validation** included for every field: numeric IDs/ages, gender
restricted to M/F/O, phone numbers checked for digit-only content and
length, emails checked for a valid `name@domain.tld` shape, and marks
constrained to the 0–100 range. Duplicate Student IDs are rejected, and
searches/updates/deletes on a non-existent ID show a clear error message.

---

## Project / Folder Structure

```
StudentManagementSystem/
│
├── main.cpp          # Program entry point: menu loop & user interaction
├── Student.h         # Student class declaration (data + method signatures)
├── Student.cpp        # Student class implementation
├── FileHandler.h      # FileHandler class declaration (file CRUD operations)
├── FileHandler.cpp    # FileHandler class implementation using fstream
├── students.txt       # Data file — sample records included for testing
└── README.md          # This file
```

### Design overview

- **`Student`** is a plain data class: it stores one student's fields and
  knows how to convert itself to/from a single line of text
  (`toFileString()` / `fromFileString()`), plus how to print itself nicely
  to the console.
- **`FileHandler`** is a small static utility class that is the *only*
  part of the program that touches `students.txt` directly. It exposes
  simple operations (`addStudent`, `loadAll`, `searchById`,
  `updateStudent`, `deleteStudent`, `idExists`, `countRecords`) built on
  top of C++ `fstream`/`ifstream`/`ofstream`.
- **`main.cpp`** contains the menu loop and all user-input handling /
  validation, and calls into `FileHandler` to perform each operation.

Records are stored one-per-line, with fields separated by a `|`
character, e.g.:

```
101|Alice Johnson|20|Female|Computer Science|2nd Year|9876543210|alice.johnson@example.com|88.50
```

This keeps the file human-readable (you can open `students.txt` in any
text editor) while remaining simple and reliable to parse.

---

## Sample Data

`students.txt` ships with 5 sample records so you can try **Display**,
**Search**, **Update**, and **Delete** immediately without first using
**Add**:

| ID  | Name          | Dept                        |
|-----|---------------|------------------------------|
| 101 | Alice Johnson | Computer Science             |
| 102 | Bob Smith     | Electronics & Communication  |
| 103 | Carla Mendes  | Mechanical Engineering       |
| 104 | David Lee     | Information Technology       |
| 105 | Esha Verma    | Civil Engineering            |

Delete this file's contents (or the file itself) if you'd rather start
with an empty database — the program automatically re-creates
`students.txt` on the next run if it's missing.

---

## How to Compile & Run

### Option 1: Command line with g++ (Windows / macOS / Linux)

1. Make sure you have a C++ compiler installed (e.g. [MinGW-w64](https://www.mingw-w64.org/)
   on Windows, or `g++` already available via Xcode Command Line Tools on
   macOS / most Linux distros).
2. Open a terminal and navigate to the project folder:
   ```bash
   cd StudentManagementSystem
   ```
3. Compile all source files together:
   ```bash
   g++ -std=c++17 -Wall -o sms main.cpp Student.cpp FileHandler.cpp
   ```
4. Run the compiled program:
   - On Linux/macOS:
     ```bash
     ./sms
     ```
   - On Windows:
     ```bash
     sms.exe
     ```

### Option 2: Visual Studio Code

1. Install the **C/C++** extension (by Microsoft) and make sure a C++
   compiler (MinGW-w64 on Windows, or the system compiler on macOS/Linux)
   is on your `PATH`.
2. Open the `StudentManagementSystem` folder in VS Code (`File > Open Folder`).
3. Open a new terminal in VS Code (`` Ctrl+` ``) and run the same compile
   command as above:
   ```bash
   g++ -std=c++17 -Wall -o sms main.cpp Student.cpp FileHandler.cpp
   ./sms
   ```
   *(Alternatively, set up a `tasks.json` build task and an `launch.json`
   debug config using the "C/C++: g++ build and debug active file"
   template, adjusting it to include all three `.cpp` files.)*

### Option 3: Code::Blocks

1. Open Code::Blocks → `File > New > Project > Console Application > C++`.
2. Name the project (e.g. `StudentManagementSystem`) and finish the wizard.
3. Replace the auto-generated `main.cpp` with this project's `main.cpp`,
   and add `Student.h`, `Student.cpp`, `FileHandler.h`, `FileHandler.cpp`
   to the project (`Project > Add files...`).
4. Copy `students.txt` into the project's working directory (the folder
   containing the compiled executable, typically `bin/Debug/`).
5. Build and run with `F9`.

### Option 4: Dev-C++

1. Open Dev-C++ → `File > New > Project > Console Application > C++`.
2. Save the project inside the `StudentManagementSystem` folder.
3. Add all the `.cpp`/`.h` files to the project (`Project > Add to Project`).
4. Make sure `students.txt` is present in the same folder as the
   generated executable.
5. Compile & Run with `F11`.

> **Note:** Regardless of which method you use, `students.txt` must be
> in the **same working directory** as the compiled executable, since
> the program opens it using a relative path. Most IDEs run the
> executable from the project folder by default; if your IDE uses a
> different output folder (e.g. `bin/Debug/`), copy `students.txt` there.

---

## Example Session

```
============================================
     STUDENT MANAGEMENT SYSTEM (C++)
============================================
 Total Records: 5
--------------------------------------------
 1. Add a new student
 2. Display all student records
 3. Search a student by ID
 4. Update existing student details
 5. Delete a student record
 6. Exit
============================================
Enter your choice (1-6): 2

===== All Student Records =====
ID    Name                Age  Gender  Department            Year/Sem    Phone         Email                      Marks
------------------------------------------------------------------------------------------------------------------------
101   Alice Johnson       20   Female  Computer Science      2nd Year    9876543210    alice.johnson@example.com  88.50
102   Bob Smith           21   Male    Electronics & Comm... 3rd Year    9123456780    bob.smith@example.com      76.25
...
```

---

## Notes for Extending the Project

- Swap the plain-text storage for a binary file by changing
  `FileHandler`'s read/write logic to use `ofstream::write` /
  `ifstream::read` with fixed-size structs, if a binary format is
  preferred.
- Add sorting (by name, marks, department) or CGPA/grade calculation as
  additional menu options — these would sit naturally as new methods on
  `FileHandler` or as free functions in `main.cpp`.
- Add a "Search by Name/Department" feature by extending `FileHandler`
  with a `searchByField`-style method.

---

## License

This project is provided as-is for educational purposes. Feel free to
use, modify, and extend it for coursework, practice, or internship
submissions.
