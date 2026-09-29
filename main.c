#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define NAME_SIZE 50
#define COURSE_SIZE 50

typedef struct
{
    int id;
    char name[NAME_SIZE];
    int age;
    char course[COURSE_SIZE];
} Student;

void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void read_line(char buffer[], int size)
{
    if (fgets(buffer, size, stdin) != NULL)
    {
        size_t length = strlen(buffer);

        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }
        else
        {
            clear_input_buffer();
        }
    }
}

void add_student(void)
{
    Student student;
    FILE *file;

    printf("\nEnter student ID: ");
    if (scanf("%d", &student.id) != 1)
    {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter name: ");
    read_line(student.name, NAME_SIZE);

    printf("Enter age: ");
    if (scanf("%d", &student.age) != 1)
    {
        printf("Invalid age.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter course: ");
    read_line(student.course, COURSE_SIZE);

    file = fopen(FILE_NAME, "ab");

    if (file == NULL)
    {
        printf("Could not open the data file.\n");
        return;
    }

    if (fwrite(&student, sizeof(Student), 1, file) != 1)
    {
        printf("Could not save the student.\n");
    }
    else
    {
        printf("Student added successfully.\n");
    }

    fclose(file);
}

void list_students(void)
{
    Student student;
    FILE *file;
    int count = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        printf("ID: %d | Name: %s | Age: %d | Course: %s\n",
               student.id, student.name, student.age, student.course);
        count++;
    }

    fclose(file);

    if (count == 0)
    {
        printf("No student records found.\n");
    }
}

void search_student(void)
{
    Student student;
    FILE *file;
    int id;
    int found = 0;

    printf("\nEnter student ID to search: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.id == id)
        {
            printf("Student found:\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("Age: %d\n", student.age);
            printf("Course: %s\n", student.course);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }
}

void delete_student(void)
{
    Student student;
    FILE *file;
    FILE *temp;
    int id;
    int found = 0;

    printf("\nEnter student ID to delete: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    temp = fopen("students_temp.dat", "wb");

    if (temp == NULL)
    {
        printf("Could not create temporary file.\n");
        fclose(file);
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.id == id)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(Student), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        if (remove(FILE_NAME) != 0 || rename("students_temp.dat", FILE_NAME) != 0)
        {
            printf("Could not update the data file.\n");
            return;
        }

        printf("Student deleted successfully.\n");
    }
    else
    {
        remove("students_temp.dat");
        printf("Student with ID %d not found.\n", id);
    }
}

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n=== Student Record System ===\n");
        printf("1. Add student\n");
        printf("2. List students\n");
        printf("3. Search student\n");
        printf("4. Delete student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number from 1 to 5.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice)
        {
            case 1:
                add_student();
                break;
            case 2:
                list_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                printf("Goodbye.\n");
                return 0;
            default:
                printf("Invalid choice. Please choose 1 to 5.\n");
        }
    }
}
