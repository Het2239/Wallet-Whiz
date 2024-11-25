#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>

struct user_expense_details {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category;
} details;

void getCurrentDate(char *month, int *day, int *year) {
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

void enterExpense(char *username) {
    

        FILE *f = fopen("Expense_details.txt", "a");
        if (f == NULL) {
            printf("                    \033[31mError opening file for writing.\033[0m\n");
            return;
        }

        struct user_expense_details details;
        printf("                    \033[34mEnter the name of the expense:\033[0m ");
        scanf(" %[^\n]s", details.name); // Reads input with spaces
        if(strlen(details.name)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }
        printf("                    \033[34mEnter a description for the expense:\033[0m ");
        scanf(" %[^\n]s", details.description); // Reads input with spaces
        if(strlen(details.description)>100){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }
        printf("                    \033[34mEnter the category (U, H, S, P, O):\033[0m ");
        scanf(" %c", &details.category); // Ensure leading space to read a single character correctly
        if (details.category == 'U' ||details.category == 'H' ||details.category == 'S' ||details.category == 'P' ||details.category == 'O' )
        {
            
        }
        else
        {
            printf("\033[31mInvalid Input!\033[0m");
            return;
        }
        
        
        printf("                    \033[34mEnter the amount:\033[0m ");
        scanf("%f", &details.amount);

        printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                    Enter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("                    Enter the month (e.g., January): ");
            scanf("%s", details.month);
            printf("                    Enter the date (e.g., 15): ");
            scanf("%d", &details.date);
            printf("                    Enter the year (e.g., 2023): ");
            scanf("%d", &details.year);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(details.month, &details.date, &details.year);
            printf("                    Using current date: \033[35m%s %d, %d\n\033[0m", details.month, details.date, details.year);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }

        // Write the details to the file in comma and space separated format
        fprintf(f, "%s, %s, %s, %c, %.2f, %s, %d, %d\n",
                username, details.name, details.description, details.category,
                details.amount, details.month, details.date, details.year);

        fclose(f);
        printf("                    \033[32mExpense recorded successfully.\033[0m\n");

       
}

void readExpense(char *username) {
    

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("                    \033[31mError opening file for reading or file does not exist.\033[0m\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\n                    Expenses for user: \033[1;33m%s\033[0m\n", username);
        printf("                    -----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0) {
                found = 1;
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        if (!found) {
            printf("                    \033[31mNo expenses found for user:\033[0m %s\n", username);
        }

        fclose(f);

        
}

void deleteExpense(char *username) {
    

        char expenseName[50];
        char month[10];
        int date, year;

        // Take input for expense name, month, date, and year to identify which record to delete
        printf("                    \033[34mEnter the name of the expense to delete:\033[0m ");
        scanf(" %[^\n]s", expenseName);
        if(strlen(expenseName)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }
        printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                    Enter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("                    Enter the month (e.g., January): ");
            scanf("%s", month);
            printf("                    Enter the date (e.g., 15): ");
            scanf("%d", &date);
            printf("                    Enter the year (e.g., 2023): ");
            scanf("%d", &year);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(month, &date, &year);
            printf("                    Using current date: \033[35m%s %d, %d\033[0m\n", month, date, year);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }

        FILE *f = fopen("Expense_details.txt", "r");
        FILE *temp = fopen("Temp_expense_details.txt", "w");
        if (f == NULL || temp == NULL) {
            printf("Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int deleted = 0;

        while (fscanf(f, "%49[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            // Check if the current record matches the input criteria for deletion
            if (strcmp(username, fileUsername) == 0 &&
                strcmp(expenseName, details.name) == 0 &&
                strcmp(month, details.month) == 0 &&
                details.date == date && details.year == year) {
                printf("                    -----------------------------------------------------------\n");
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
                printf("                    Is this the record you want to delete (1. Yes / 0. No) :");
                int ch=0;
                scanf("%d",&ch);
                if (ch==0)
                {
                    return;
                }
                
                deleted = 1; // Mark the expense as found and delete it by not writing to the temp file
            } else {
                // Write non-matching records to the temp file
                fprintf(temp, "%s, %s, %s, %c, %.2f, %s, %d, %d\n",
                        fileUsername, details.name, details.description, details.category,
                        details.amount, details.month, details.date, details.year);
            }
        }

        fclose(f);
        fclose(temp);

        // Replace the original file with the updated file if deletion was successful
        if (deleted) {
            remove("Expense_details.txt");
            rename("Temp_expense_details.txt", "Expense_details.txt");
            printf("                    \033[32mExpense deleted successfully.\033[0m\n");
        } else {
            remove("Temp_expense_details.txt");
            printf("                    \033[31mNo matching expense found for deletion.\033[0m\n");
        }

        
}

void editExpense(char *username) {
    

        char expenseName[50];
        char month[10];
        int date, year;

        // Take input for expense name, month, date, and year to identify which record to delete
        printf("                    \033[34mEnter the name of the expense to edit\033[0m: ");
        scanf(" %[^\n]s", expenseName);
        if(strlen(expenseName)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }
        printf("                    \033[34mEnter the month of the expense to edit (e.g., January):\033[0m ");
        scanf("%s", month);
        printf("                    \033[34mEnter the date of the expense to edit (e.g., 15):\033[0m ");
        scanf("%d", &date);
        printf("                    \033[34mEnter the year of the expense to edit (e.g., 2024):\033[0m ");
        scanf("%d", &year);

        

        FILE *f = fopen("Expense_details.txt", "r");
        FILE *temp = fopen("Temp_expense_details.txt", "w");
        if (f == NULL || temp == NULL) {
            printf("                    \033[31mError opening file.\033[0m\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        struct user_expense_details data;
        int deleted = 0;

        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            // Check if the current record matches the input criteria for deletion
            if (strcmp(username, fileUsername) == 0 &&
                strcmp(expenseName, details.name) == 0 &&
                strcmp(month, details.month) == 0 &&
                details.date == date && details.year == year) {
                    printf("                    -----------------------------------------------------------\n");
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
                printf("                    Is this the record you want to edit (1. Yes / 0. No) :");
                int ch=0;
                scanf("%d",&ch);
                if (ch==0)
                {
                    return;
                }
                
                printf("                    \033[34mEnter the new name of the Expense:\033[0m ");
                scanf(" %[^\n]s", data.name);
                if(strlen(data.name)>50){
                    printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
                }
                printf("                    \033[34mEnter a new description for the Expense:\033[0m ");
                scanf(" %[^\n]s", data.description); // Reads input with spaces
                if(strlen(data.description)>100){
                    printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
                }
                printf("                    \033[34mEnter the category (U, H, S, P, O):\033[0m ");
                scanf(" %c", &data.category); // Ensure leading space to read a single character correctly
                if (data.category == 'U' ||data.category == 'H' ||data.category == 'S' ||data.category == 'P' ||data.category == 'O' )
                {
                    
                }
                else
                {
                    printf("\033[31mInvalid Input!\033[0m");
                    return;
                }
                printf("                    \033[34mEnter the new amount:\033[0m ");
                scanf("%f", &data.amount);

                printf("                    Would you like to:\n                    1. Enter the new date manually\n                    2. Use the current date\n                   Enter your choice : ");
                int dateChoice;
                scanf("%d", &dateChoice);

                if (dateChoice == 1) {
                    // Manual date input
                    printf("                    Enter the month (e.g., January): ");
                    scanf("%s", data.month);
                    printf("                    Enter the date (e.g., 15): ");
                    scanf("%d", &data.date);
                    printf("                    Enter the year (e.g., 2023): ");
                    scanf("%d", &data.year);
                } else if (dateChoice == 2) {
                    // Get current date automatically
                    getCurrentDate(data.month, &data.date, &data.year);
                    printf("                    Using current date: %s %d, %d\n", data.month, data.date, data.year);
                } else {
                    printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
                    return;
                }

                deleted = 1; // Mark the expense as found and delete it by not writing to the temp file
            } else {
                // Write non-matching records to the temp file
                fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                        fileUsername, details.name, details.description,
                        details.amount, details.month, details.date, details.year);
            }
        }

        fclose(f);

        // Replace the original file with the updated file if deletion was successful
        if (deleted) {
            fprintf(temp, "%s, %s, %s, %c, %.2f, %s, %d, %d\n",
                    username, data.name, data.description, data.category,
                    data.amount, data.month, data.date, data.year);
            fclose(temp);
            remove("Expense_details.txt");
            rename("Temp_expense_details.txt", "Expense_details.txt");
            printf("                    \033[32mExpense Edited successfully.\033[0m\n");
        } else {
            remove("Temp_expense_details.txt");
            printf("                    \033[31mNo matching expense found to edit.\033[0m\n");
        }

        
}


void expenseOnCategory(char *username) {
    

        char cat;
        printf("\033[34mEnter the category of expense you want to view (U, H, S, P, O):\033[0m ");
        scanf(" %c", &cat);
        if (cat == 'U' ||cat == 'H' ||cat == 'S' ||cat == 'P' ||cat == 'O' )
                {
                    
                }
                else
                {
                    printf("\033[31mInvalid Input!\033[0m");
                    return;
                }

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("                    \033[31mError opening file.\033[0m\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\n                    Expenses for user: \033[1;33m%s\033[0m\n", username);
        printf("                    -----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && cat == details.category) {
                found = 1;
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        if (!found) {
            printf("                    \033[31mNo expenses found for category %c for user:\033[0m %s\n", cat, username);
        }

        fclose(f);

        
}

void totalmonthlyExpense(char *username) {
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

        char monthcheck[10];
        int yearcheck;
        int date;
        float totalexp = 0;

        printf("                    Would you like to:\n                    1. Enter the month manually\n                    2. Use the current month\n                    Enter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("                    Enter the month (e.g., January): ");
            scanf("%s", monthcheck);
            
            printf("                    Enter the year (e.g., 2023): ");
            scanf("%d", &yearcheck);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(monthcheck, &date, &yearcheck);
            printf("                    Using current Month: \033[35m%s %d\n\033[0m", monthcheck, yearcheck);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }
        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s viewed monthly expense for %s, %d on %02d %s, %04d at %02d:%02d:%02d\n",username,monthcheck,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("                    \033[31mError opening file.\033[0m\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(monthcheck, details.month) == 0 && yearcheck == details.year) {
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
                totalexp += details.amount;
                found = 1;
            }
        }

        fclose(f);

        if (found) {
            printf("                    The total monthly expense for %s in %s %d is: \033[31m%.2f\033[0m\n", username, monthcheck, yearcheck, totalexp);
        } else {
            printf("                    No expenses found for user %s in %s %d\n", username, monthcheck, yearcheck);
        }

        
}

void totalyearlyExpense(char *username) {
    
        FILE *logf=NULL;
        int yearcheck;
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

        float totalexp = 0;

        printf("                    Would you like to:\n                    1. Enter the year manually\n                    2. Use the current year\n                    Enter your choice : ");
        int dateChoice;
        char monthcheck[10];
        int date;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            
            
            printf("                    Enter the year (e.g., 2023): ");
            scanf("%d", &yearcheck);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(monthcheck, &date, &yearcheck);
            printf("                    Using current Year: %d\n", yearcheck);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }

        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s viewed yearly expense for %d on %02d %s, %04d at %02d:%02d:%02d\n",username,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);

        FILE *f = fopen("Expense_details.txt", "r");

        if (f == NULL) {
            printf("                    Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\n                    Expense statements for user: \033[1;33m%s\033[0m\n", username);
        printf("                    -----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n", 
                      fileUsername, details.name, details.description, &details.category, 
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && yearcheck == details.year) {
                found = 1;
                totalexp += details.amount;
                printf("                    \033[1;31mName:\033[0m %s\n", details.name);
                printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;31mCategory:\033[0m %c\n", details.category);
                printf("                    \033[1;31mAmount:\033[0m %.2f\n", details.amount);
                printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        fclose(f);

        if (found) {
            printf("                    The total yearly expense for %s in %d is: \033[31m%.2f\033[0m\n", username, yearcheck, totalexp);
        } else {
            printf("                    No expenses found for user %s in %d\n", username, yearcheck);
        }

        
}


struct Node {
    struct user_expense_details s;
    struct Node *next;
};

struct Node *head = NULL;

// Function to add a new expense to the linked list
void add_expense(struct user_expense_details details) {
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Copy details to the new node
    strcpy(newnode->s.name, details.name);
    strcpy(newnode->s.description, details.description);
    newnode->s.category = details.category;
    newnode->s.amount = details.amount;
    strcpy(newnode->s.month, details.month);
    newnode->s.date = details.date;
    newnode->s.year = details.year;
    newnode->next = NULL;

    // Insert at the end of the list
    if (head == NULL) {
        head = newnode;
    } else {
        struct Node *buffernode = head;
        while (buffernode->next != NULL) {
            buffernode = buffernode->next;
        }
        buffernode->next = newnode;
    }
}

// Function to save expense details to a file
void save_expense_to_file(struct user_expense_details details, const char *filename, char *username) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    fprintf(file, "%s, %s, %s, %c, %.2f, %s, %d, %d\n", 
            username, details.name, details.description, details.category,
            details.amount, details.month, details.date, details.year);
    
    fclose(file);
}

// Function to generate recurring expenses and save them to a file
void generate_recurring_expense(struct user_expense_details base_expense, int interval_days, int num_periods,char *username) {
    time_t current_time;
    struct tm *time_info;
    time(&current_time);
    time_info = localtime(&current_time);

    for (int i = 0; i < num_periods; i++) {
        time_info->tm_mday += interval_days; // Add the interval days
        mktime(time_info); // Normalize the time structure

        // Create a copy of the base expense with the updated date
        struct user_expense_details new_expense = base_expense;
        new_expense.date = time_info->tm_mday;
        new_expense.year = time_info->tm_year + 1900;
        strftime(new_expense.month, 10, "%B", time_info); // Get the month name

        add_expense(new_expense);
        save_expense_to_file(new_expense, "Expense_details.txt",username); // Save to the recurring expense file
    }
}

void addReccuringexpense(char *username){
    struct user_expense_details new_expense;

    // User input and saving to file
    printf("                    \033[34mEnter the name of the expense:\033[0m ");
        scanf(" %[^\n]s", new_expense.name); // Reads input with spaces
        if(strlen(new_expense.name)>50){
            printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        }
        printf("                    \033[34mEnter a description for the expense:\033[0m ");
        scanf(" %[^\n]s", new_expense.description); // Reads input with spaces
        if(strlen(new_expense.description)>100){
            printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        }
        printf("                    \033[34mEnter the category (U, H, S, P, O):\033[0m ");
        scanf(" %c", &new_expense.category); // Ensure leading space to read a single character correctly
        if (new_expense.category == 'U' ||new_expense.category == 'H' ||new_expense.category == 'S' ||new_expense.category == 'P' ||new_expense.category == 'O' )
        {
            
        }
        else
        {
            printf("\033[31mInvalid Input!\033[0m");
            return;
        }
        
        
        printf("                    \033[34mEnter the amount:\033[0m ");
        scanf("%f", &new_expense.amount);

        printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                    Enter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("                    Enter the month (e.g., January): ");
            scanf("%s", new_expense.month);
            printf("                    Enter the date (e.g., 15): ");
            scanf("%d", &new_expense.date);
            printf("                    Enter the year (e.g., 2023): ");
            scanf("%d", &new_expense.year);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(new_expense.month, &new_expense.date, &new_expense.year);
            printf("                    Using current date: \033[35m%s %d, %d\n\033[0m", new_expense.month, new_expense.date, new_expense.year);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }

        printf("                    Enter the time duration of the recurring expense (in Days..) : ");
        int d=0;
        scanf("%d",&d);
        printf("                    Enter the no. of times you want this expense to be added : ");
        int n=0;
        scanf("%d",&n);

    // Save user input to input file
    save_expense_to_file(new_expense, "Expense_details.txt",username);

    // Add to linked list and generate recurring expenses
    add_expense(new_expense);
    generate_recurring_expense(new_expense, d, n,username);
}

