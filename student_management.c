#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int rollNumber;
    char name[50];
    float grade;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();
void sortStudents();

void clearInputBuffer() {
    while (getchar() != '\n'); // Clear the input buffer
}

int main() {
    int choice;
    printf("Welcome to the Student Management System\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Modify Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        clearInputBuffer();  // Clear the newline left by scanf

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void searchStudent() {
    int rollNo;
    printf("Enter roll number to search: ");
    if (scanf("%d", &rollNo) != 1) {  // Check if input is a valid integer
        printf("Invalid input. Please enter a valid number.\n");
        clearInputBuffer();  // Clear the buffer
        return;  // Exit the function to avoid further incorrect behavior
    }

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNo) {
            printf("Found Student - Roll No: %d, Name: %s, Grade: %.2f\n", students[i].rollNumber, students[i].name, students[i].grade);
            found = 1;
            break;
        }
    }

    if (found==0) {
        printf("Student not found.\n");
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Error: Cannot add more students. Maximum limit reached.\n");
        return;
    }

    printf("Enter roll number: ");
    if (scanf("%d", &students[studentCount].rollNumber) != 1) {
        printf("Invalid input for roll number.\n");
        clearInputBuffer();  // Clear invalid input
        return;
    }

    clearInputBuffer();  // Clear the newline left by scanf

    printf("Enter name: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0';  // Remove newline character

    printf("Enter grade: ");
    if (scanf("%f", &students[studentCount].grade) != 1) {
        printf("Invalid input for grade.\n");
        clearInputBuffer();  // Clear invalid input
        return;
    }

    studentCount++;
    printf("Student added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo students to display.\n");
        return;
    }

    // Sort students by roll number before displaying
    sortStudents();

    printf("\nStudent List (sorted by roll number):\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Roll No: %d, Name: %s, Grade: %.2f\n", students[i].rollNumber, students[i].name, students[i].grade);
    }
}

void sortStudents() {
    // Simple bubble sort to sort the students by roll number in ascending order
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].rollNumber > students[j].rollNumber) {
                // Swap the students
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void modifyStudent() {
    int rollNo;
    printf("Enter roll number to modify: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid input for roll number.\n");
        clearInputBuffer();  // Clear invalid input
        return;
    }

    clearInputBuffer();  // Clear the newline character left by scanf for rollNo

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNo) {
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';  // Remove newline character

            printf("Enter new grade: ");
            if (scanf("%f", &students[i].grade) != 1) {
                printf("Invalid input for grade.\n");
                clearInputBuffer();  // Clear invalid input
                return;
            }

            printf("Student record updated successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    int rollNo;
    printf("Enter roll number to delete: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid input for roll number.\n");
        clearInputBuffer();  // Clear invalid input
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNo) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];  // Shift elements left
            }
            studentCount--;  // Decrease the count of students
            printf("Student deleted successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}
