#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void createUser();
void readUsers();
void updateUser();
void deleteUser();
void initializeFile();

int main() {
    int choice;
    initializeFile();

    while (1) {
        printf("\nCRUD Operations on File:\n");
        printf("1. Add a new user (Create)\n");
        printf("2. Display all users (Read)\n");
        printf("3. Modify user details by ID (Update)\n");
        printf("4. Remove a user by ID (Delete)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                createUser(); 
                break;
            case 2: 
                readUsers(); 
                break;
            case 3: 
                updateUser(); 
                break;
            case 4: 
                deleteUser(); 
                break;
            case 5: 
                exit(0);
            default: 
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Ensure the file exists
void initializeFile() {
    FILE *file = fopen(FILENAME, "a");
    if (file) 
        fclose(file);
}

// Add a new user
void createUser() {
    User user;
    FILE *file = fopen(FILENAME, "a");

    printf("Enter User ID: ");
    scanf("%d", &user.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", user.name);
    printf("Enter Age: ");
    scanf("%d", &user.age);

    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added successfully.\n");
}

// Display all users
void readUsers() {
    FILE *file = fopen(FILENAME, "r");
    User user;

    printf("\nUser Records:\n");
    printf("ID\tName\t\tAge\n");
    printf("----------------------------------\n");
    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        printf("%d\t%-15s\t%d\n", user.id, user.name, user.age);
    }

    fclose(file);
}

// Update a user by ID
void updateUser() {
    int id, found = 0;
    User user;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter User ID to update: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", user.name);
            printf("Enter new Age: ");
            scanf("%d", &user.age);
        }
        fprintf(temp, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("User updated successfully.\n");
    else
        printf("User with ID %d not found.\n", id);
}

// Delete a user by ID
void deleteUser() {
    int id, found = 0;
    User user;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            continue; // Skip writing this user to the temp file
        }
        fprintf(temp, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("User deleted successfully.\n");
    else
        printf("User with ID %d not found.\n", id);
}