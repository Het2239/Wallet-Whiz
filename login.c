#include "login.h"

int registerUser(struct user_data *user) {
    FILE *f = fopen("credentials.txt", "a+");
    if (f == NULL) {
        printf("                    \033[31mError opening file for writing.\033[0m\n");
        return 0;
    }

    printf("                    \033[36mEnter a username:\033[0m ");
    scanf("%s", user->username);
    if(strlen(user->username)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return 0;
    }
    char urename[50];
    char psd[50];
    while (fscanf(f,"%s %s",urename,psd) != EOF)
    {
        if(strcmp(urename,user->username)==0){
            printf("                    \033[31mUsername Already Exists Try Another\033[0m\n");
            return 0;
        }
    }
    
    printf("                    \033[36mEnter a password:\033[0m ");
    scanf("%s", user->password);
    if(strlen(user->password)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return 0;

    }

    fprintf(f, "%s %s\n", user->username, user->password); // Store credentials in the file
    fclose(f);

    printf("                    \033[32mRegistration successful!\033[0m\n");
    return 1;
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
    if(strlen(user->username)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return 0;
    }
    char urename[50];
    char psd[50];
    int check=0;
    while (fscanf(f,"%s %s",urename,psd) != EOF)
    {
        if(strcmp(urename,user->username) != 0){
            
            check=0;
        }
        else{
            check=1;
            break;

        }
    }

    if (check==0)
    {
        printf("                    \033[31mNo Such Username Exists please try again or Register if you haven't.\033[0m\n");
        return 0;
    }
    
    
    
    printf("                    \033[36mEnter your password:\033[0m ");
    scanf("%s", user->password);
    if(strlen(user->password)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return 0;

    }
    fclose(f);
    f = fopen("credentials.txt", "r");
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
