#include<stdio.h>
#include "login.h"

int main() {
    int choice;
    struct user_data user;

    printf("1. Register\n");
    printf("2. Login\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerUser(&user);
            printf("Login to get started.");
        case 2:
        int flag=0;
        do
        {
            int stat = loginUser(&user);
            if (stat)
            {
                 // main block
            }
            
            printf("1. Try Again\n0. Exit\nEnter your choice : ");
            int choice=0;
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                flag=1;
                break;
            case 0:
                flag=0;
                break;
            
            default:
                flag=1;
                break;
            }
        } while (flag=1);
        
            

            break;

        case 0:
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
