#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_NAME 20

struct Directory {
    char file_names[MAX_FILES][MAX_NAME];
    int file_count;
};

int main() {
    struct Directory dir;
    dir.file_count = 0;

    int choice;
    char filename[MAX_NAME];

    while (1) {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. List Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1: // Create File
            printf("Enter file name to create: ");
            scanf("%s", filename);

            // Check if file already exists
            int exists = 0;
            for (int i = 0; i < dir.file_count; i++) {
                if (strcmp(dir.file_names[i], filename) == 0) {
                    exists = 1;
                    break;
                }
            }

            if (exists) {
                printf("File already exists!\n");
            } else {
                strcpy(dir.file_names[dir.file_count], filename);
                dir.file_count++;
                printf("File created successfully.\n");
            }
            break;

        case 2: // Delete File
            printf("Enter file name to delete: ");
            scanf("%s", filename);
            int found = 0;
            for (int i = 0; i < dir.file_count; i++) {
                if (strcmp(dir.file_names[i], filename) == 0) {
                    // Shift remaining files
                    for (int j = i; j < dir.file_count - 1; j++) {
                        strcpy(dir.file_names[j], dir.file_names[j + 1]);
                    }
                    dir.file_count--;
                    found = 1;
                    printf("File deleted successfully.\n");
                    break;
                }
            }
            if (!found) {
                printf("File not found.\n");
            }
            break;

        case 3: // Search File
            printf("Enter file name to search: ");
            scanf("%s", filename);
            int search_found = 0;
            for (int i = 0; i < dir.file_count; i++) {
                if (strcmp(dir.file_names[i], filename) == 0) {
                    search_found = 1;
                    printf("File found at position %d.\n", i + 1);
                    break;
                }
            }
            if (!search_found) {
                printf("File not found.\n");
            }
            break;

        case 4: // List Files
            if (dir.file_count == 0) {
                printf("Directory is empty.\n");
            } else {
                printf("Files in directory:\n");
                for (int i = 0; i < dir.file_count; i++) {
                    printf("%s\n", dir.file_names[i]);
                }
            }
            break;

        case 5: // Exit
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
