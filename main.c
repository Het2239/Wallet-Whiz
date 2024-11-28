#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include"login.h"
#include"expense.h"
#include"income.h"
#include"report.h"
#include"savings.h"

void banner(){
    printf("                                             =========================================================================                   \n");
    printf("                                             ||                         \033[33m$_$  WalletWhiz  $_$\033[0m                        ||                   \n");
    printf("                                             ||---------------------------------------------------------------------||                   \n");
    printf("                                             ||                   \033[32mWelcome to Smart Money Tracking!\033[0m                  ||                   \n");
    printf("                                             =========================================================================                   \n");
    printf("\n\n\n\n\n\n");
    return;
}
void showProgressBar(int percentage) {
    int barWidth = 50; // Width of the progress bar
    int pos = barWidth * percentage / 100; // Calculate the position of the bar

    printf("\t\t\t\t\t\t\t[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            printf("\033[33m#\033[0m"); // Completed part
        } else {
            printf(" "); // Remaining part
        }
    }
    printf("] %d%%\r", percentage); // Print percentage
    fflush(stdout); // Ensure the output is updated immediately
}

void getCurrentDateTime(int *day, int *month, int *year, int *hour, int *minute, int *second) {
    // Get the current time
    time_t currentTime;
    time(&currentTime);

    // Convert to local time
    struct tm *localTime = localtime(&currentTime);

    // Retrieve date and time components
    *day = localTime->tm_mday;
    *month = localTime->tm_mon;  // 0-based index (0 = January)
    *year = localTime->tm_year + 1900;
    *hour = localTime->tm_hour;
    *minute = localTime->tm_min;
    *second = localTime->tm_sec;
}

// Array of month names
const char *monthNames[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


int main() {
    int itr=1;
    int day, month, year, hour, minute, second;
    while (itr)
    {
      
    
    int choice;
    struct user_data user;
    system("clear");
    banner();
    printf("                    \033[35m1. Register\033[0m\n");
    printf("                    \033[35m2. Login\033[0m\n");
    printf("                    \033[35m0. Exit\033[0m\n");
    printf("                    \033[35mEnter your choice:\033[0m ");
    scanf("%d", &choice);
    FILE *logf=NULL;
    switch (choice) {
        case 1:
            system("clear");
            banner();
            int flg=0;
            do
            {
                flg=registerUser(&user);
            } while (flg==0);
            logf=fopen("log.txt","a");
            getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
            fprintf(logf,"User : %s registered an account on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
            fclose(logf);
            
            
            
        case 2:
        int flag=0;
        system("clear");
        
        do
        {
            banner();
            printf("                    \033[34mLogin to get started.\033[0m\n");
            int stat = loginUser(&user);
            
            if (stat == 1)
            {   
                logf=fopen("log.txt","a");
                getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                fprintf(logf,"User : %s logined in account on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                fclose(logf);
                printf("\n\n\n\t\t\t\t\t\t\t\t\t\033[32mloading Sources!!!\033[0m\n\n");
                for (int i = 0; i <= 100; ++i) {
                    showProgressBar(i); // Update progress bar
                    usleep(10000); // Pause for 10 milliseconds (adjust as needed)
                }
                

                int mflag=0;
                do{
                flag=0;
                
                system("clear");
                banner();
                printf("               \t\t\t\t     ==========================================================================\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 1 ]   Add Expense\033[0m                    \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 2 ]   Add Recurring Expense\033[0m          \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 3 ]   Edit Expense\033[0m                   \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 4 ]   Delete Expense\033[0m                 \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 5 ]   View all Expense\033[0m               \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 6 ]   View monthly Expense\033[0m           \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 7 ]   View yearly Expense\033[0m            \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 8 ]   View Expense based on Category\033[0m \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 9 ]   Add Income\033[0m                     \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 10 ]  Edit Income\033[0m                    \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 11 ]  Delete Income\033[0m                  \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 12 ]  View all Income\033[0m                \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 13 ]  View monthly Income\033[0m            \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 14 ]  View yearly Income\033[0m             \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 15 ]  View monthly Report\033[0m            \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 16 ]  View yearly Report\033[0m             \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 17 ]  View Total Savings\033[0m             \t\t      |\n");
                printf("               \t\t\t\t     |\t\t      \033[36m[ 0 ]   Exit\033[0m                           \t\t      |\n");
                printf("               \t\t\t\t     ==========================================================================\n\n");
                printf("               \t\t\t\t      \t\t\t      \033[36mEnter your Choice :\033[0m");
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
                        logf=fopen("log.txt","a");time_t currentTime;
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s added an expense on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);

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
                    int f6=0;
                    do
                    {
                        addReccuringexpense(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s added a recurring expense on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);

                        printf("\n                    \033[32m1. Run again\033[0m\n");
                        printf("                    \033[31m0. Exit\033[0m\n");
                        int choice=0;
                        printf("                    \033[36mEnter your choice :\033[0m ");
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
                case 3:
                    system("clear");
                    banner();
                    int f2=0;
                    do
                    {
                        editExpense(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s edited an expense on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);

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
                case 4:
                    system("clear");
                    banner();
                    int f3=0;
                    do
                    {
                        deleteExpense(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s deleted an expense on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);

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
                case 5:
                    
                    system("clear");
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed all expense on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    banner();
                   
                        
                    readExpense(user.username);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 6:
                    
                    system("clear");
                    
                    banner();
                    
                    totalmonthlyExpense(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed monthly expense satatements on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                        
                    mflag=1;
                    break;
                case 7:
                    
                    system("clear");
                    banner();
                    
                    totalyearlyExpense(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed yearly expense statements on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous input
                        
                        
                        
                    mflag=1;
                    break;
                case 8:
                    int f7=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        expenseOnCategory(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s viewed expense for a category on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);
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
                case 9:
                    int f8=0;
                    system("clear");
                    banner();
                    do
                    {
                        
                        addIncome(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s added an income on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);
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
                case 10:
                    int f9=0;
                    system("clear");
                    banner();
                    do
                    {
                        editIncome(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s edited an income on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);
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
                case 11:
                    int f10=0;
                    system("clear");
                    banner();
                    do
                    {
                        deleteIncome(user.username);
                        logf=fopen("log.txt","a");
                        getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                        fprintf(logf,"User : %s deleted an income on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                        fclose(logf);

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
                case 12:
                    
                    system("clear");
                    banner();
                    
                    viewIncome(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed all income statements on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 13:
                    
                    system("clear");
                    banner();
                   
                    monthlyIncome(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed monthly income statements on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 14:
                    
                    system("clear");
                    banner();
                    
                    yearlyIncome(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed yearly income statements on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu
                        
                    mflag=1;
                    break;
                case 15:
                    
                    system("clear");
                    banner();
                    
                        
                    monthlyexpenseReport(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed monthly expense report on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                    mflag=1;
                    break;
                case 16:
                    
                    system("clear");
                    banner();
                    
                        
                    yearlyexpenseReport(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed yearly Expense report on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                    mflag=1;
                    break;
                case 17:
                    
                    system("clear");
                    banner();
                    
                        
                    savings(user.username);
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s viewed all savings on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
                    printf("\n\n\n\t\t\t\t\033[3;34mPress Enter to continue...\033[0m");
                    getchar(); // Wait for user input to continue
                    getchar(); // Handle newline from previous inpu

                    mflag=1;
                    break;
                
                
                
                case 0:
                    mflag=0;
                    system("clear");
                    logf=fopen("log.txt","a");
                    getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                    fprintf(logf,"User : %s exited the program on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                    fclose(logf);
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
                logf=fopen("log.txt","a");
                getCurrentDateTime(&day, &month, &year, &hour, &minute, &second);
                fprintf(logf,"User : %s failed to login on %02d %s, %04d at %02d:%02d:%02d\n",user.username,day, monthNames[month], year, hour, minute, second);
                fclose(logf);
                printf("                    \033[32m1. Try Again\033[0m\n                    \033[31m0. Exit\033[0m\n                    \033[36mEnter your choice :\033[0m ");
                int choice=0;
                scanf("%d",&choice);
                switch (choice)
                {
                case 1:
                    system("clear");
                    flag=1;
                    break;
                case 0:
                    system("clear");
                    flag=0;
                    
                    break;
                
                default:
                    system("clear");
                    flag=1;
                    break;
                }
            }
        } while (flag==1);
        break;
        

            

            

        case 0:
            system("clear");
            itr=0;
            break;

        default:
            printf("                    \033[31mInvalid choice.\033[0m\n");
            itr=0;
            break;
    }
    }
    return 0;
}
