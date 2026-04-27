#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;
    int choice;

    // Open file in read/write binary mode
    filePtr = fopen("employee.dat", "rb+");
    
    // If file doesn't exist, create it
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Employee Database Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);
                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                // Move file pointer to the specific record position
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                printf("Employee details added successfully.\n");
                break;

            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                // Read from file and check if read was successful
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) > 0) {
                    printf("\nEmployee Details:\n");
                    printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.empId, emp.empName, emp.empSalary);
                } else {
                    printf("Employee record not found.\n");
                }
                break;

            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) > 0) {
                    printf("Updating details for ID %d:\n", emp.empId);
                    printf("Enter New Name: ");
                    scanf("%s", emp.empName);
                    printf("Enter New Salary: ");
                    scanf("%f", &emp.empSalary);

                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                    printf("Employee details updated successfully.\n");
                } else {
                    printf("Employee record not found.\n");
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    fclose(filePtr);
    return 0;
}