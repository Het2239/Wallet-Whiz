#include "login.h"

void registerUser(struct user_data *user) {
    FILE *f = fopen("credentials.txt", "a");
    if (f == NULL) {
        printf("                    \033[31mError opening file for writing.\033[0m\n");
        return;
    }

    printf("                    \033[36mEnter a username:\033[0m ");
    scanf("%s", user->username);
    printf("                    \033[36mEnter a password:\033[0m ");
    scanf("%s", user->password);

    fprintf(f, "%s %s\n", user->username, user->password); // Store credentials in the file
    fclose(f);

    printf("                    \033[32mRegistration successful!\033[0m\n");
}

int loginUser(struct user_data *user) {
    FILE *f = fopen("credentials.txt", "r");
    if (f == NULL) {
        printf("                    \033[31mError opening file for reading or no registered users.\033[0m\n");
        return 0;
    }

    char storedUsername[50];
    char storedPassword[50];
    int found = 0;

    printf("                    \033[36mEnter your username:\033[0m ");
    scanf("%s", user->username);
    printf("                    \033[36mEnter your password:\033[0m ");
    scanf("%s", user->password);

    while (fscanf(f, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(user->username, storedUsername) == 0 && strcmp(user->password, storedPassword) == 0) {
            found = 1;

            break;
        }
    }

    fclose(f);

    if (found) {
        printf("                    \033[32mLogin successful!\033[0m\n");
        return 1;
    } else {
        printf("                    \033[31mInvalid username or password.\033[0m\n");
        return 0;
    }
}
