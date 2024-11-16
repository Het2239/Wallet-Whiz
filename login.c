#include "login.h"

void registerUser(struct user_data *user) {
    FILE *f = fopen("credentials.txt", "a");
    if (f == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    printf("Enter a username: ");
    scanf("%s", user->username);
    printf("Enter a password: ");
    scanf("%s", user->password);

    fprintf(f, "%s %s\n", user->username, user->password); // Store credentials in the file
    fclose(f);

    printf("Registration successful!\n");
}

int loginUser(struct user_data *user) {
    FILE *f = fopen("credentials.txt", "r");
    if (f == NULL) {
        printf("Error opening file for reading or no registered users.\n");
        return;
    }

    char storedUsername[50];
    char storedPassword[50];
    int found = 0;

    printf("Enter your username: ");
    scanf("%s", user->username);
    printf("Enter your password: ");
    scanf("%s", user->password);

    while (fscanf(f, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(user->username, storedUsername) == 0 && strcmp(user->password, storedPassword) == 0) {
            found = 1;

            break;
        }
    }

    fclose(f);

    if (found) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}
