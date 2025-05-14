#include <stdio.h>
#include <string.h>

#define MAX 100 // Maximum number of parking slots

// Structure to store vehicle information
struct Vehicle {
    char number[20]; // Vehicle number
    char type[10];   // Vehicle type
    int slot;        // Assigned parking slot
};

// Global variables
struct Vehicle parking[MAX]; // Array to store parked vehicles
int count = 0;               // Number of vehicles currently parked

// Login function (max 3 attempts)
int login() {
    char username[20], password[20];
    const char correctUsername[] = "admin";
    const char correctPassword[] = "1234";

    printf("=== LOGIN REQUIRED ===\n");

    for (int attempts = 3; attempts > 0; attempts--) {
        printf("Username: ");
        scanf("%19s", username);
        printf("Password: ");
        scanf("%19s", password);

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("Login successful!\n");
            return 1;
        } else {
            printf("Invalid credentials. Attempts left: %d\n", attempts - 1);
        }
    }

    printf("Access denied. Program exiting...\n");
    return 0;
}


