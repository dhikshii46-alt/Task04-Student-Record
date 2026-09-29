# Task 04 — Student Record System

## What this program does

This C program manages student records using a `struct` and a binary file.

It supports:

- Add a student
- List all students
- Search for a student by ID
- Delete a student by ID
- Save records to a file so they remain available after the program exits

## Requirements covered

- `Student` struct for each record
- Add, list, search, and delete operations
- Binary file persistence using `students.dat`
- File-open and input checks
- Delete operation uses a temporary file and then replaces the original data file

## How to compile

```bash
gcc main.c -o student_records
```

## How to run

Linux/macOS:

```bash
./student_records
```

Windows:

```bash
student_records.exe
```

## Example

```text
=== Student Record System ===
1. Add student
2. List students
3. Search student
4. Delete student
5. Exit
Enter your choice: 1

Enter student ID: 101
Enter name: Arun
Enter age: 20
Enter course: C Programming
Student added successfully.
```

Choose option `2` to list records, `3` to search by ID, and `4` to delete by ID.

The records are stored in `students.dat` in the same folder as the program.
