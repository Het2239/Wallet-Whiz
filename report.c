#include<stdio.h>
#include<string.h>
#include<time.h>
#include<float.h>

struct user_income_details1 {
    char name[50];
    char description[100];
    float amount;
    char month[10];
    int date;
    int year;
};

struct user_expense_details1 {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category;
};

void getCurrentDater(char *month, int *day, int *year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Convert numerical month to a month name (e.g., 1 -> "January")
    char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    strcpy(month, months[tm.tm_mon]);
    *day = tm.tm_mday;
    *year = tm.tm_year + 1900;
}


void monthlyexpenseReport(char *username) {
    char monthcheck[10];
    int yearcheck;
    int date = 0;
    float totalinc = 0;

    printf("                    Would you like to:\n                    1. Enter the month manually\n                    2. Use the current month\n                    Enter your choice: ");
    int dateChoice;
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        // Manual date input
        printf("                    Enter the month to view your report (e.g., January): ");
        scanf("%s", monthcheck);
        printf("                    Enter the year to check your monthly report (e.g., 2024): ");
        scanf("%d", &yearcheck);
    } else if (dateChoice == 2) {
        // Get current date automatically
        getCurrentDater(monthcheck, &date, &yearcheck);
        printf("                    Using current month: %s, %d\n", monthcheck, yearcheck);
    } else {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }
    FILE *logf=NULL;
        
        const char *monthNames[] = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
        };

        // Get the current time
        time_t currentTime;
        time(&currentTime);

        // Convert to local time
        struct tm *localTime = localtime(&currentTime);

        // Get day, month, year, hour, minute, second
        int day = localTime->tm_mday;
        int month = localTime->tm_mon; // 0-based index (0 = January)
        int year = localTime->tm_year + 1900;
        int hour = localTime->tm_hour;
        int minute = localTime->tm_min;
        int second = localTime->tm_sec;

        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s viewed monthly expense report for month %s, %d on %02d %s, %04d at %02d:%02d:%02d\n",username,monthcheck,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);

    FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("                    Error opening file.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details1 details;
    int found = 0;

    // Variables to track maximum and minimum incomes
    float maxIncome = -1;
    float minIncome = FLT_MAX;
    struct user_income_details1 maxIncomeDetails;
    struct user_income_details1 minIncomeDetails;

    printf("\n                    Income statements for user: %s\n", username);
    printf("                    -----------------------------------------------------------\n");

    // Reading income data
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && yearcheck == details.year && strcmp(monthcheck, details.month) == 0) {
            found = 1;
            totalinc += details.amount;

            // Check for max and min income
            if (details.amount > maxIncome) {
                maxIncome = details.amount;
                maxIncomeDetails = details;
            }
            if (details.amount < minIncome) {
                minIncome = details.amount;
                minIncomeDetails = details;
            }

            printf("                    \033[1;32mName:\033[0m %s\n", details.name);
            printf("                    \033[1;32mDescription:\033[0m %s\n", details.description);
            printf("                    \033[1;32mAmount:\033[0m %.2f\n", details.amount);
            printf("                    \033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
            printf("                    -----------------------------------------------------------\n");
        }
    }
    fclose(f);

    if (found) {
        printf("                    The total monthly income for %s in %s %d is: %.2f\n", username, monthcheck, yearcheck, totalinc);
        printf("                    -----------------------------------------------------------\n");
        printf("                    Maximum Income: \033[32m%.2f\033[0m (Name: %s, Description: %s, Date: %s %d, %d)\n", maxIncome, maxIncomeDetails.name, maxIncomeDetails.description, maxIncomeDetails.month, maxIncomeDetails.date, maxIncomeDetails.year);
        printf("                    Minimum Income: \033[32m%.2f\033[0m (Name: %s, Description: %s, Date: %s %d, %d)\n", minIncome, minIncomeDetails.name, minIncomeDetails.description, minIncomeDetails.month, minIncomeDetails.date, minIncomeDetails.year);
        printf("                    -----------------------------------------------------------\n");
    } else {
        printf("                    No income found for user %s in %s %d\n", username, monthcheck, yearcheck);
        printf("                    -----------------------------------------------------------\n");
    }

    // Expense report
    f = fopen("Expense_details.txt", "r");
    if (f == NULL) {
        printf("                    Error opening file.\n");
        return;
    }

    struct user_expense_details1 detail;
    float totalexp = 0;
    found = 0;

    // Variables to track maximum and minimum expenses
    float maxExpense = -1;
    float minExpense = FLT_MAX;
    struct user_expense_details1 maxExpenseDetails;
    struct user_expense_details1 minExpenseDetails;
    float totalsave=0.0;
    printf("\n                    Expense statements for user: %s\n", username);
    printf("                    -----------------------------------------------------------\n");

    // Reading expense data
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                  fileUsername, detail.name, detail.description, &detail.category,
                  &detail.amount, detail.month, &detail.date, &detail.year) != EOF) {
                  if(strcmp(username, fileUsername) == 0 && strcmp(monthcheck, detail.month) == 0 && yearcheck == detail.year && detail.category=='S'){
                totalsave+=detail.amount;
            }
        if (strcmp(username, fileUsername) == 0 && strcmp(monthcheck, detail.month) == 0 && yearcheck == detail.year && detail.category!='S') {
            found = 1;
            
            totalexp += detail.amount;

            // Check for max and min expense
            if (detail.amount > maxExpense) {
                maxExpense = detail.amount;
                maxExpenseDetails = detail;
            }
            if (detail.amount < minExpense) {
                minExpense = detail.amount;
                minExpenseDetails = detail;
            }

            printf("                    \033[1;31mName:\033[0m %s\n", detail.name);
            printf("                    \033[1;31mDescription:\033[0m %s\n", detail.description);
            printf("                    \033[1;31mCategory:\033[0m %c\n", detail.category);
            printf("                    \033[1;31mAmount:\033[0m %.2f\n", detail.amount);
            printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", detail.month, detail.date, detail.year);
            printf("                    -----------------------------------------------------------\n");
        }
    }
    fclose(f);

    if (found) {
        printf("                    The total monthly expense for %s in %s %d is: %.2f\n", username, monthcheck, yearcheck, totalexp);
        printf("                    -----------------------------------------------------------\n");
        printf("                    Maximum Expense: \033[31m%.2f\033[0m (Name: %s, Description: %s, Category: %c, Date: %s %d, %d)\n", maxExpense, maxExpenseDetails.name, maxExpenseDetails.description, maxExpenseDetails.category, maxExpenseDetails.month, maxExpenseDetails.date, maxExpenseDetails.year);
        printf("                    Minimum Expense: \033[31m%.2f\033[0m (Name: %s, Description: %s, Category: %c, Date: %s %d, %d)\n", minExpense, minExpenseDetails.name, minExpenseDetails.description, minExpenseDetails.category, minExpenseDetails.month, minExpenseDetails.date, minExpenseDetails.year);
        printf("                    -----------------------------------------------------------\n");
    } else {
        printf("                    No expenses found for user %s in %s %d\n", username, monthcheck, yearcheck);
        printf("                    -----------------------------------------------------------\n");
    }

    float money=0;
    printf("                    Total Income : \033[32m%.2f\033[0m\n",totalinc);
    printf("                    Total Expense : \033[31m%.2f\033[0m\n",totalexp);
    printf("                    Total Savings : \033[32m%.2f\033[0m\n",totalsave);
    money=totalinc-totalexp+totalsave;
    if (money>=0)
    {
        printf("                    Balance available : \033[0;32m%.2f\033[0m\n",money);
    }
    else
    {
        printf("                    Balance available : \033[0;31m%.2f\033[0m\n",money);
    }
    
    
}


void yearlyexpenseReport(char *username){
    char monthcheck[10];
    int yearcheck;
    int date = 0;
    float totalinc = 0;

    printf("                    Would you like to:\n                    1. Enter the year manually\n                    2. Use the current year\n                    Enter your choice: ");
    int dateChoice;
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        // Manual date input
        
        printf("                    Enter the year to check your yearly report (e.g., 2024): ");
        scanf("%d", &yearcheck);
    } else if (dateChoice == 2) {
        // Get current date automatically
        getCurrentDater(monthcheck, &date, &yearcheck);
        printf("                    Using current year: %d\n", yearcheck);
    } else {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }
    FILE *logf=NULL;
        
        const char *monthNames[] = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
        };

        // Get the current time
        time_t currentTime;
        time(&currentTime);

        // Convert to local time
        struct tm *localTime = localtime(&currentTime);

        // Get day, month, year, hour, minute, second
        int day = localTime->tm_mday;
        int month = localTime->tm_mon; // 0-based index (0 = January)
        int year = localTime->tm_year + 1900;
        int hour = localTime->tm_hour;
        int minute = localTime->tm_min;
        int second = localTime->tm_sec;

        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s viewed yearly expense report for year %d on %02d %s, %04d at %02d:%02d:%02d\n",username,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);
    FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("                    Error opening file.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details1 details;
    int found = 0;

    // Variables to track maximum and minimum incomes
    float maxIncome = -1;
    float minIncome = FLT_MAX;
    struct user_income_details1 maxIncomeDetails;
    struct user_income_details1 minIncomeDetails;

    printf("\n                    Income statements for user: %s\n", username);
    printf("                    -----------------------------------------------------------\n");

    // Reading income data
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && yearcheck == details.year ) {
            found = 1;
            totalinc += details.amount;

            // Check for max and min income
            if (details.amount > maxIncome) {
                maxIncome = details.amount;
                maxIncomeDetails = details;
            }
            if (details.amount < minIncome) {
                minIncome = details.amount;
                minIncomeDetails = details;
            }

            printf("                    \033[1;32mName:\033[0m %s\n", details.name);
            printf("                    \033[1;32mDescription:\033[0m %s\n", details.description);
            printf("                    \033[1;32mAmount:\033[0m %.2f\n", details.amount);
            printf("                    \033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
            printf("                    -----------------------------------------------------------\n");
        }
    }
    fclose(f);

    if (found) {
        printf("                    The total yearly income for %s in %d is: \033[32m%.2f\033[0m\n", username, yearcheck, totalinc);
        printf("                    -----------------------------------------------------------\n");
        printf("                    Maximum Income: \033[32m%.2f\033[0m (Name: %s, Description: %s, Date: %s %d, %d)\n", maxIncome, maxIncomeDetails.name, maxIncomeDetails.description, maxIncomeDetails.month, maxIncomeDetails.date, maxIncomeDetails.year);
        printf("                    Minimum Income: \033[32m%.2f\033[0m (Name: %s, Description: %s, Date: %s %d, %d)\n", minIncome, minIncomeDetails.name, minIncomeDetails.description, minIncomeDetails.month, minIncomeDetails.date, minIncomeDetails.year);
        printf("                    -----------------------------------------------------------\n");
    } else {
        printf("                    No income found for user %s in %d\n", username, yearcheck);
        printf("                    -----------------------------------------------------------\n");
    }

    // Expense report
    f = fopen("Expense_details.txt", "r");
    if (f == NULL) {
        printf("                    \033[31mError opening file.\033[0m\n");
        return;
    }

    struct user_expense_details1 detail;
    float totalexp = 0;
    found = 0;

    // Variables to track maximum and minimum expenses
    float maxExpense = -1;
    float minExpense = FLT_MAX;
    struct user_expense_details1 maxExpenseDetails;
    struct user_expense_details1 minExpenseDetails;
    float totalsave=0.0;
    printf("\n                    Expense statements for user: %s\n", username);
    printf("                    -----------------------------------------------------------\n");

    // Reading expense data
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                  fileUsername, detail.name, detail.description, &detail.category,
                  &detail.amount, detail.month, &detail.date, &detail.year) != EOF) {
                    if(strcmp(username, fileUsername) == 0 && detail.category=='S' && yearcheck==detail.year){
                totalsave += detail.amount;
            }
        if (strcmp(username, fileUsername) == 0 && yearcheck == detail.year && detail.category!='S') {
            found = 1;
            
            totalexp += detail.amount;

            // Check for max and min expense
            if (detail.amount > maxExpense) {
                maxExpense = detail.amount;
                maxExpenseDetails = detail;
            }
            if (detail.amount < minExpense) {
                minExpense = detail.amount;
                minExpenseDetails = detail;
            }

            printf("                    \033[1;31mName:\033[0m %s\n", detail.name);
            printf("                    \033[1;31mDescription:\033[0m %s\n", detail.description);
            printf("                    \033[1;31mCategory:\033[0m %c\n", detail.category);
            printf("                    \033[1;31mAmount:\033[0m %.2f\n", detail.amount);
            printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", detail.month, detail.date, detail.year);
            printf("                    -----------------------------------------------------------\n");
        }
    }
    fclose(f);

    if (found) {
        printf("                    The total yearly expense for %s in %d is: \033[31m%.2f\033[0m\n", username, yearcheck, totalexp);
        printf("                    -----------------------------------------------------------\n");
        printf("                    Maximum Expense: \033[31m%.2f\033[m (Name: %s, Description: %s, Category: %c, Date: %s %d, %d)\n", maxExpense, maxExpenseDetails.name, maxExpenseDetails.description, maxExpenseDetails.category, maxExpenseDetails.month, maxExpenseDetails.date, maxExpenseDetails.year);
        printf("                    Minimum Expense: \033[31m%.2f\033[m (Name: %s, Description: %s, Category: %c, Date: %s %d, %d)\n", minExpense, minExpenseDetails.name, minExpenseDetails.description, minExpenseDetails.category, minExpenseDetails.month, minExpenseDetails.date, minExpenseDetails.year);
        printf("                    -----------------------------------------------------------\n");
    } else {
        printf("                    No expenses found for user %s in %d\n", username, yearcheck);
        printf("                    -----------------------------------------------------------\n");
    }

    float money=0;
    printf("                    Total Income : \033[32m%.2f\n\033[0m",totalinc);
    printf("                    Total Expense : \033[31m%.2f\n\033[0m",totalexp);
    printf("                    Total Savings : \033[32m%.2f\n\033[0m",totalsave);
    money=totalinc-totalexp+totalsave;
    if (money>=0)
    {
        printf("                    Balance available : \033[0;32m%.2f\033[0m\n",money);
    }
    else
    {
        printf("                    Balance available : \033[0;31m%.2f\033[0m\n",money);
    }
    
    
}

