#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"login.h"
#include"expense.h"
#include"income.h"
#include"report.h"

void banner(){
    printf("                                                               =========================================================================                   \n");
    printf("                                                               ||                         \033[33m$_$  Expensify  $_$\033[0m                         ||                   \n");
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
    printf("                    1. Register\n");
    printf("                    2. Login\n");
    printf("                    0. Exit\n");
    printf("                    Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("clear");
            banner();
            registerUser(&user);
            printf("                    Login to get started.\n");
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
                printf("                    1. Add Expense\n");
                printf("                    2. Edit Expense\n");
                printf("                    3. Delete Expense\n");
                printf("                    4. View all Expense\n");
                printf("                    5. View monthly Expense\n");
                printf("                    6. View yearly Expense\n");
                printf("                    7. View Expense based on Category\n");
                printf("                    8. Add Income\n");
                printf("                    9. Edit Income\n");
                printf("                    10. Delete Income\n");
                printf("                    11. View all Income\n");
                printf("                    12. View monthly Income\n");
                printf("                    13. View yearly Income\n");
                printf("                    14. View monthly Report\n");
                printf("                    15. View yearly Report\n");
                printf("                    0. Exit\n");
                printf("                    Enter your Choioce : ");
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

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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
                    int f4=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        readExpense(user.username);
                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f4=1;
                            break;
                        case 0:
                            f4=0;
                            break;
                        
                        }
                    } while (f4==1);
                    mflag=1;
                    break;
                case 5:
                    int f5=0;
                    system("clear");
                    banner();
                    do
                    {
                        totalmonthlyExpense(user.username);

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f5=1;
                            break;
                        case 0:
                            f5=0;
                            break;
                        
                        }
                    } while (f5==1);
                    mflag=1;
                    break;
                case 6:
                    int f6=0;
                    system("clear");
                    banner();
                    do
                    {
                        totalyearlyExpense(user.username);

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f6=1;
                            break;
                        case 0:
                            f6=0;
                            break;
                        
                        }
                    } while (f6==1);
                    mflag=1;
                    break;
                case 7:
                    int f7=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        expenseOnCategory(user.username);
                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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
                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
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
                    int f11=0;
                    system("clear");
                    banner();
                    do
                    {
                        viewIncome(user.username);

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f11=1;
                            break;
                        case 0:
                            f11=0;
                            break;
                        
                        }
                    } while (f11==1);
                    mflag=1;
                    break;
                case 12:
                    int f12=0;
                    system("clear");
                    banner();
                    do
                    {
                        monthlyIncome(user.username);

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f12=1;
                            break;
                        case 0:
                            f12=0;
                            break;
                        
                        }
                    } while (f12==1);
                    mflag=1;
                    break;
                case 13:
                    int f13=0;
                    system("clear");
                    banner();
                    do
                    {
                        yearlyIncome(user.username);

                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f13=1;
                            break;
                        case 0:
                            f13=0;
                            break;
                        
                        }
                    } while (f13==1);
                    mflag=1;
                    break;
                case 14:
                    int f14=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        monthlyexpenseReport(user.username);
                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f14=1;
                            break;
                        case 0:
                            f14=0;
                            break;
                        
                        }
                    } while (f14==1);
                    mflag=1;
                    break;
                case 15:
                    int f15=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        yearlyexpenseReport(user.username);
                        printf("\n                    1. Run again\n");
                        printf("                    0. Exit\n");
                        int choice=0;
                        printf("                    Enter your choice : ");
                        scanf("%d",&choice);
                        
                        switch (choice)
                        {
                        case 1:
                            f15=1;
                            break;
                        case 0:
                            f15=0;
                            break;
                        
                        }
                    } while (f15==1);
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
                printf("                    1. Try Again\n                  0. Exit\n               Enter your choice : ");
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
            printf("                    Invalid choice.\n");
            break;
    }

    return 0;
}
