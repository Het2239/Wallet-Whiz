#include<stdio.h>
#include "login.h"

int main() {
    int choice;
    struct user_data user;

    printf("1. Register\n");
    printf("2. Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerUser(&user);
            break;
        case 2:
            loginUser(&user);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
