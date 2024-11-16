#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"login.h"
#include"expense.h"
#include"income.h"
#include"report.h"

void banner(){
    printf("                                                               =========================================================================                   \n");
    printf("                                                               ||                         \033[33m$_$  WalletWhiz  $_$\033[0m                        ||                   \n");
    printf("                                                               ||---------------------------------------------------------------------||                   \n");
    printf("                                                               ||                   \033[32mWelcome to Smart Money Tracking!\033[0m                  ||                   \n");
    printf("                                                               =========================================================================                   \n");
    printf("\n\n\n\n\n\n");
    return;
}

int main() {
    int choice;
    struct user_data user;
    system("clear");
    banner();
    printf("                    \033[35m1. Register\033[0m\n");
    printf("                    \033[35m2. Login\033[0m\n");
    printf("                    \033[35m0. Exit\033[0m\n");
    printf("                    \033[35mEnter your choice:\033[0m ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("clear");
            banner();
            registerUser(&user);
            printf("                    \033[34mLogin to get started.\033[0m\n");
        case 2:
        int flag=0;
        system("clear");
        do
        {
            banner();
            int stat = loginUser(&user);
            
            if (stat == 1)
            {   int mflag=0;
                do{
                flag=0;
                
                system("clear");
                banner();
                printf("                    \033[36m1. Add Expense\033[0m\n");
                printf("                    \033[36m2. Edit Expense\033[0m\n");
                printf("                    \033[36m3. Delete Expense\033[0m\n");
                printf("                    \033[36m4. View all Expense\033[0m\n");
                printf("                    \033[36m5. View monthly Expense\033[0m\n");
                printf("                    \033[36m6. View yearly Expense\033[0m\n");
                printf("                    \033[36m7. View Expense based on Category\033[0m\n");
                printf("                    \033[36m8. Add Income\033[0m\n");
                printf("                    \033[36m9. Edit Income\033[0m\n");
                printf("                    \033[36m10. Delete Income\033[0m\n");
                printf("                    \033[36m11. View all Income\033[0m\n");
                printf("                    \033[36m12. View monthly Income\033[0m\n");
                printf("                    \033[36m13. View yearly Income\033[0m\n");
                printf("                    \033[36m14. View monthly Report\033[0m\n");
                printf("                    \033[36m15. View yearly Report\033[0m\n");
                printf("                    \033[36m0. Exit\033[0m\n");
                printf("                    \033[36mEnter your Choioce :\033[0m ");
                int pchoice=0;
                scanf("%d",&pchoice);
                switch (pchoice)
                {
                case 1:
                    system("clear");
                    banner();
                    int f1=0;
                    do
                    {
                        enterExpense(user.username);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f1=1;
                            break;
                        case 0:
                            f1=0;
                            break;
                        
                        }
                    } while (f1==1);
                    mflag=1;
                    break;
                case 2:
                    system("clear");
                    banner();
                    int f2=0;
                    do
                    {
                        editExpense(user.username);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f2=1;
                            break;
                        case 0:
                            f2=0;
                            break;
                        
                        }
                    } while (f2==1);
                    mflag=1;
                    break;
                case 3:
                    system("clear");
                    banner();
                    int f3=0;
                    do
                    {
                        deleteExpense(user.username);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f3=1;
                            break;
                        case 0:
                            f3=0;
                            break;
                        
                        }
                    } while (f3==1);
                    mflag=1;
                    break;
                case 4:
                    
                    system("clear");
                    banner();
                   
                        
                    readExpense(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 5:
                    
                    system("clear");
                    banner();
                    
                    totalmonthlyExpense(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                        
                    mflag=1;
                    break;
                case 6:
                    
                    system("clear");
                    banner();
                    
                    totalyearlyExpense(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous input
                        
                        
                        
                    mflag=1;
                    break;
                case 7:
                    int f7=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        expenseOnCategory(user.username);
                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f7=1;
                            break;
                        case 0:
                            f7=0;
                            break;
                        
                        }
                    } while (f7==1);
                    mflag=1;
                    break;
                case 8:
                    int f8=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        addIncome(user.username);
                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f8=1;
                            break;
                        case 0:
                            f8=0;
                            break;
                        
                        }
                    } while (f8==1);
                    mflag=1;
                    break;
                case 9:
                    int f9=0;
                    system("clear");
                    banner();
                    do
                    {
                        editIncome(user.username);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f9=1;
                            break;
                        case 0:
                            f9=0;
                            break;
                        
                        }
                    } while (f9==1);
                    mflag=1;
                    break;
                case 10:
                    int f10=0;
                    system("clear");
                    banner();
                    do
                    {
                        deleteIncome(user.username);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f10=1;
                            break;
                        case 0:
                            f10=0;
                            break;
                        
                        }
                    } while (f10==1);
                    mflag=1;
                    break;
                case 11:
                    
                    system("clear");
                    banner();
                    
                    viewIncome(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 12:
                    
                    system("clear");
                    banner();
                   
                    monthlyIncome(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 13:
                    
                    system("clear");
                    banner();
                    
                    yearlyIncome(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 14:
                    
                    system("clear");
                    banner();
                    
                        
                    monthlyexpenseReport(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                    mflag=1;
                    break;
                case 15:
                    
                    system("clear");
                    banner();
                    
                        
                    yearlyexpenseReport(user.username);
                    printf("\nPress Enter to continue...");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                    mflag=1;
                    break;
                
                
                
                case 0:
                    mflag=0;
                    system("clear");
                    break;
                default:
                    mflag=0;
                    system("clear");
                    break;
                }
            }while(mflag==1);
                // main block
            }
            else{
                printf("                    \033[32m1. Try Again\033[0m\n                    \033[31m0. Exit\033[0m\n                    \033[36mEnter your choice :\033[0m ");
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
            }
        } while (flag==1);
        
            

            break;

        case 0:
            break;

        default:
            printf("                    \033[31mInvalid choice.\033[0m\n");
            break;
    }

    return 0;
}
