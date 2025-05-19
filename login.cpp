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



// Load data from file
void loadFromFile() {
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%19s %9s %d", parking[count].number, parking[count].type, &parking[count].slot) == 3) {
        count++;
    }

    fclose(file);
}

// Save data to file
void saveToFile() {
    FILE *file = fopen("parking.txt", "w");
    if (file == NULL) {
        printf("Error saving data to file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %d\n", parking[i].number, parking[i].type, parking[i].slot);
    }

    fclose(file);
}

// Add a new vehicle
void addVehicle() {
    if (count >= MAX) {
        printf("Parking lot is full!\n");
        return;
    }

    printf("Enter vehicle number: ");
    scanf("%19s", parking[count].number);

    printf("Enter vehicle type: ");
    scanf("%9s", parking[count].type);

    parking[count].slot = count + 1;
    printf("Vehicle parked at slot number %d\n", parking[count].slot);

    count++;
}

// Remove a vehicle
void removeVehicle() {
    char number[20];
    int found = 0;

    printf("Enter vehicle number to remove: ");
    scanf("%19s", number);

    for (int i = 0; i < count; i++) {
        if (strcmp(parking[i].number, number) == 0) {
            // Shift all vehicles after this one
            for (int j = i; j < count - 1; j++) {
                parking[j] = parking[j + 1];
                parking[j].slot = j + 1; // Update slot number
            }
            count--;
            found = 1;
            printf("Vehicle removed successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Vehicle not found!\n");
    }
}
// display vehicles
void displayVehicles() {
    if (count == 0) {
        printf("No vehicles parked.\n");
        return;
    }
    printf("Parked Vehicles:\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s Slot: %d\n", parking[i].number, parking[i].type, parking[i].slot);
    }
}
// search vehicles
void searchVehicle() {
    char number[20];
    int found = 0;
    printf("Enter vehicle number to search: ");
    scanf("%s", number);

    for (int i = 0; i < count; i++) {
        if (strcmp(parking[i].number, number) == 0) {
            printf("Vehicle found at slot %d. Type: %s\n", parking[i].slot, parking[i].type);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Vehicle not found!\n");
    }
}
void totalVehicles(){
	printf("Total Parked Vehicles:%d \n",count);
}

void availableSlots(){
	printf("Available Parking Slots:%d \n", MAX - count);
}
void clearAllRecords() {
    char confirm;
    printf(“Are you sure you want to clear all parking data? (y/n): “);
    scanf(“%c”, &confirm); // Note the space before %c to catch leftover newline

    if (confirm == ‘y’ || confirm == ‘Y’) {
        count = 0;
        FILE *file = fopen(“parking.txt”, “W”); // Clears file
        fclose(file);
        printf(“All records cleared. \n”);
    } else {
        printf(“Cancelled.\n”);
    }
}


// Main Menu
int main() {
    if (!login()) return 0;
    loadFromFile();

    int choice;
    while (1) {
        printf("\n----- Vehicle Parking Management -----\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Display All Vehicles\n");
        printf("4. Search Vehicle by Number\n");
        printf("5. Total Parked Vehicles\n");
        printf("6. Show Available Parking Slots\n");
        printf("7. Clear All Records\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

