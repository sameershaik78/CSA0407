#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10
#define MAX_NAME 20

struct UserDirectory {
    char username[MAX_NAME];
    char files[MAX_FILES][MAX_NAME];
    int file_count;
};

int main() {
    struct UserDirectory users[MAX_USERS];
    int user_count = 0;

    int choice;
    char uname[MAX_NAME], fname[MAX_NAME];

    while (1) {
        printf("\n--- Two Level Directory ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. List Files\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int i, j, found;

        switch (choice) {

        case 1: // Create User Directory
            printf("Enter username: ");
            scanf("%s", uname);
            found = 0;

            for (i = 0; i < user_count; i++) {
                if (strcmp(users[i].username, uname) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("User directory already exists.\n");
            } else {
                strcpy(users[user_count].username, uname);
                users[user_count].file_count = 0;
                user_count++;
                printf("User directory created successfully.\n");
            }
            break;

        case 2: // Create File
            printf("Enter username: ");
            scanf("%s", uname);
            printf("Enter file name to create: ");
            scanf("%s", fname);
            found = 0;

            for (i = 0; i < user_count; i++) {
                if (strcmp(users[i].username, uname) == 0) {
                    found = 1;
                    // Check if file already exists
                    int exists = 0;
                    for (j = 0; j < users[i].file_count; j++) {
                        if (strcmp(users[i].files[j], fname) == 0) {
                            exists = 1;
                            break;
                        }
                    }

                    if (exists) {
                        printf("File already exists for this user.\n");
                    } else {
                        strcpy(users[i].files[users[i].file_count], fname);
                        users[i].file_count++;
                        printf("File created successfully.\n");
                    }
                    break;
                }
            }
            if (!found) {
                printf("User directory not found.\n");
            }
            break;

        case 3: // Delete File
            printf("Enter username: ");
            scanf("%s", uname);
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            found = 0;

            for (i = 0; i < user_count; i++) {
                if (strcmp(users[i].username, uname) == 0) {
                    found = 1;
                    int file_found = 0;
                    for (j = 0; j < users[i].file_count; j++) {
                        if (strcmp(users[i].files[j], fname) == 0) {
                            file_found = 1;
                            // Shift files
                            for (int k = j; k < users[i].file_count - 1; k++) {
                                strcpy(users[i].files[k], users[i].files[k + 1]);
                            }
                            users[i].file_count--;
                            printf("File deleted successfully.\n");
                            break;
                        }
                    }
                    if (!file_found) {
                        printf("File not found.\n");
                    }
                    break;
                }
            }
            if (!found) {
                printf("User directory not found.\n");
            }
            break;

        case 4: // Search File
            printf("Enter username: ");
            scanf("%s", uname);
            printf("Enter file name to search: ");
            scanf("%s", fname);
            found = 0;

            for (i = 0; i < user_count; i++) {
                if (strcmp(users[i].username, uname) == 0) {
                    found = 1;
                    int file_found = 0;
                    for (j = 0; j < users[i].file_count; j++) {
                        if (strcmp(users[i].files[j], fname) == 0) {
                            file_found = 1;
                            printf("File found at position %d in %s's directory.\n", j + 1, uname);
                            break;
                        }
                    }
                    if (!file_found) {
                        printf("File not found.\n");
                    }
                    break;
                }
            }

            if (!found) {
                printf("User directory not found.\n");
            }
            break;

        case 5: // List Files
            printf("Enter username: ");
            scanf("%s", uname);
            found = 0;

            for (i = 0; i < user_count; i++) {
                if (strcmp(users[i].username, uname) == 0) {
                    found = 1;
                    if (users[i].file_count == 0) {
                        printf("No files in %s's directory.\n", uname);
                    } else {
                        printf("Files in %s's directory:\n", uname);
                        for (j = 0; j < users[i].file_count; j++) {
                            printf("%s\n", users[i].files[j]);
                        }
                    }
                    break;
                }
            }

            if (!found) {
                printf("User directory not found.\n");
            }
            break;

        case 6:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
