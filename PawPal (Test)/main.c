#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ANIMALS 10
#define MAX_NAME_LENGTH 50

// Define Animal structure
struct Animal {
    int id;
    char name[MAX_NAME_LENGTH];
    char type[MAX_NAME_LENGTH];
    int age;
    char healthStatus[MAX_NAME_LENGTH];
    int isAdopted; // 0 = not adopted, 1 = adopted
};

// Function to convert a string to lowercase
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to check if an ID is unique
int isIdUnique(struct Animal animals[], int animalCount, int id) {
    for (int i = 0; i < animalCount; i++) {
        if (animals[i].id == id) {
            return 0; // ID is not unique
        }
    }
    return 1; // ID is unique
}

// Function to display currently used IDs
void displayUsedIds(struct Animal animals[], int animalCount) {
    printf("Currently used IDs: ");
    for (int i = 0; i < animalCount; i++) {
        printf("%d ", animals[i].id);
    }
    printf("\n");
}

int main() {
    struct Animal animals[MAX_ANIMALS];
    int animalCount = 5; // Start with 5 animals pre-defined
    int choice;

    // Pre-fill some animals
    animals[0] = (struct Animal){1, "Buddy", "Dog", 3, "Healthy", 0};
    animals[1] = (struct Animal){2, "Whiskers", "Cat", 2, "Healthy", 0};
    animals[2] = (struct Animal){3, "Charlie", "Dog", 4, "Healthy", 0};
    animals[3] = (struct Animal){4, "Max", "Dog", 5, "Healthy", 0};
    animals[4] = (struct Animal){5, "Luna", "Cat", 1, "Healthy", 0};

    while (1) {
        printf("\nAdoption System Menu:\n");
        printf("1. Add Animal\n");
        printf("2. Display Available Animals\n");
        printf("3. Adopt Animal\n");
        printf("4. List Adopted Animals\n");
        printf("5. Search Animal by Name or Type\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Add Animal
            if (animalCount < MAX_ANIMALS) {
                int newId;

                // Display currently used IDs
                displayUsedIds(animals, animalCount);

                // Get a unique ID from the user
                do {
                    printf("Enter animal ID (unique): ");
                    scanf("%d", &newId);

                    if (!isIdUnique(animals, animalCount, newId)) {
                        printf("ID %d is already taken. Please enter a different ID.\n", newId);
                    }
                } while (!isIdUnique(animals, animalCount, newId));

                animals[animalCount].id = newId;

                // Gather remaining details
                printf("Enter animal name: ");
                scanf(" %[^\n]%*c", animals[animalCount].name);
                printf("Enter animal type (e.g., Dog, Cat): ");
                scanf(" %[^\n]%*c", animals[animalCount].type);
                printf("Enter animal age: ");
                scanf("%d", &animals[animalCount].age);
                printf("Enter animal health status: ");
                scanf(" %[^\n]%*c", animals[animalCount].healthStatus);
                animals[animalCount].isAdopted = 0;

                animalCount++;
                printf("Animal added successfully!\n");
            } else {
                printf("Animal limit reached. Can't add more animals.\n");
            }
        } else if (choice == 2) {
            // Display Available Animals
            printf("\nAvailable Animals for Adoption:\n");
            for (int i = 0; i < animalCount; i++) {
                if (animals[i].isAdopted == 0) {
                    printf("ID: %d, Name: %s, Type: %s, Age: %d, Health Status: %s\n",
                        animals[i].id, animals[i].name, animals[i].type,
                        animals[i].age, animals[i].healthStatus);
                }
            }
        } else if (choice == 3) {
            // Adopt Animal
            int animalId;
            printf("Enter the ID of the animal you want to adopt: ");
            scanf("%d", &animalId);

            int found = 0;
            for (int i = 0; i < animalCount; i++) {
                if (animals[i].id == animalId && animals[i].isAdopted == 0) {
                    found = 1;
                    animals[i].isAdopted = 1;
                    printf("You have adopted %s!\n", animals[i].name);
                    break;
                }
            }

            if (!found) {
                printf("Animal with ID %d is not available for adoption.\n", animalId);
            }
        } else if (choice == 4) {
            // List Adopted Animals
            printf("\nAdopted Animals:\n");
            for (int i = 0; i < animalCount; i++) {
                if (animals[i].isAdopted == 1) {
                    printf("ID: %d, Name: %s, Type: %s, Age: %d, Health Status: %s\n",
                        animals[i].id, animals[i].name, animals[i].type,
                        animals[i].age, animals[i].healthStatus);
                }
            }
        } else if (choice == 5) {
            // Search Animal by Name or Type
            char searchTerm[MAX_NAME_LENGTH];
            printf("Enter the name or type of animal to search: ");
            scanf(" %[^\n]%*c", searchTerm);

            toLowerCase(searchTerm);

            printf("\nSearch Results:\n");
            for (int i = 0; i < animalCount; i++) {
                char animalName[MAX_NAME_LENGTH];
                char animalType[MAX_NAME_LENGTH];

                strcpy(animalName, animals[i].name);
                strcpy(animalType, animals[i].type);
                toLowerCase(animalName);
                toLowerCase(animalType);

                if (strstr(animalName, searchTerm) != NULL || strstr(animalType, searchTerm) != NULL) {
                    printf("ID: %d, Name: %s, Type: %s, Age: %d, Health Status: %s\n",
                        animals[i].id, animals[i].name, animals[i].type,
                        animals[i].age, animals[i].healthStatus);
                }
            }
        } else if (choice == 6) {
            // Exit Program
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}



