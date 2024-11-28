#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct user_income_details {
    char name[50];
    char description[100];
    float amount;
    char month[10];
    int date;
    int year;
};

void getCurrentDatei(char *month, int *day, int *year) {
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

void addIncome(char *username) {
   
    struct user_income_details detail;
    FILE *f = fopen("Income_details.txt", "a");
    if (f == NULL) {
        printf("                    \033[31mError opening file for writing.\033[0m\n");
        return;
    }

    printf("                    \033[34mEnter the name of the Income:\033[0m ");
    scanf(" %[^\n]s", detail.name);
    if(strlen(detail.name)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return;
    }
    printf("                    \033[34mEnter a description for the Income:\033[0m ");
    scanf(" %[^\n]s", detail.description); // Reads input with spaces
    if(strlen(detail.description)>100){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }
    printf("                    \033[34mEnter the amount:\033[0m ");
    scanf("%f", &detail.amount);

    printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                     Enter your choice : ");
    int dateChoice;
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        // Manual date input
        printf("                    \033[36mEnter the month (e.g., January):\033[0m ");
        scanf("%s", detail.month);
        printf("                    \033[36mEnter the date (e.g., 15):\033[0m ");
        scanf("%d", &detail.date);
        printf("                    \033[36mEnter the year (e.g., 2023):\033[0m ");
        scanf("%d", &detail.year);
    } else if (dateChoice == 2) {
        // Get current date automatically
        getCurrentDatei(detail.month, &detail.date, &detail.year);
        printf("                    Using current date: \033[33m%s %d, %d\033[0m\n", detail.month, detail.date, detail.year);
    } else {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }

    // Write the details to the file in comma and space-separated format
    fprintf(f, "%s, %s, %s, %.2f, %s, %d, %d\n",
            username, detail.name, detail.description,
            detail.amount, detail.month, detail.date, detail.year);

    fclose(f);
    printf("                    \033[32mIncome recorded successfully.\033[0m\n");

    
}

void deleteIncome(char *username) {

    char incomeName[50];
    char fileUsername[50];
    struct user_income_details details;
    int deleted = 0;
    int serialNo = 0;  // Counter for serial numbers

    // Take input for income name to filter matching records
    printf("                    \033[34mEnter the name of the Income to delete:\033[0m ");
    scanf(" %[^\n]s", incomeName);
    if (strlen(incomeName) > 50) {
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
        return;
    }

    FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("                    \033[31mError opening file for reading.\033[0m\n");
        return;
    }

    printf("\n\t\t\033[34mMatching incomes for '%s':\033[0m\n", incomeName);
    printf("                    -----------------------------------------------------------\n");

    // Display matching incomes with serial numbers
    struct user_income_details matchedIncomes[100]; // Store matching records temporarily
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(incomeName, details.name) == 0) {
            matchedIncomes[serialNo] = details; // Store matching record
            printf("                    \033[1;31m[%d]\033[0m\n", serialNo + 1); // Display serial number
            printf("                    \033[1;31mDescription:\033[0m %s\n", details.description);
            printf("                    \033[1;31mAmount:\033[0m \033[32m%.2f\033[0m\n", details.amount);
            printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
            printf("                    -----------------------------------------------------------\n");
            serialNo++;
        }
    }

    fclose(f);

    if (serialNo == 0) {
        // No matching incomes found
        printf("                    \033[31mNo matching incomes found for '%s'.\033[0m\n", incomeName);
        return;
    }

    // Ask user to choose the serial number of the income to delete
    printf("                    \033[34mEnter the serial number of the income to delete:\033[0m ");
    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > serialNo) {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }

    // Reopen file to filter out the chosen income
    f = fopen("Income_details.txt", "r");
    FILE *temp = fopen("Temp_income_details.txt", "w");
    if (temp == NULL) {
        printf("                    \033[31mError opening temporary file for writing.\033[0m\n");
        fclose(f);
        return;
    }

    serialNo = 0; // Reset serialNo for comparison
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(incomeName, details.name) == 0) {
            serialNo++;
            if (serialNo == choice) {
                // Skip writing the chosen record to delete it
                deleted = 1;
                continue;
            }
        }
        // Write all other records to the temporary file
        fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                fileUsername, details.name, details.description,
                details.amount, details.month, details.date, details.year);
    }

    fclose(f);
    fclose(temp);

    // Replace the original file with the updated file if deletion was successful
    if (deleted) {
        remove("Income_details.txt");
        rename("Temp_income_details.txt", "Income_details.txt");
        printf("                    \033[32mIncome deleted successfully.\033[0m\n");
    } else {
        remove("Temp_income_details.txt");
        printf("                    \033[31mFailed to delete the income.\033[0m\n");
    }
}

void editIncome(char *username) {
    char incomeName[50];
    char month[10];
    int date, year;
    int dateChoice;

    // Prompt user for income details to edit
    printf("                    \033[34mEnter the name of the Income to edit:\033[0m ");
    scanf(" %[^\n]s", incomeName);
    if(strlen(incomeName)>50){
        printf("                    \033[31mLength Exceeded! Try Again.\033[0m\n");
    }

    printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                    Enter your choice: ");
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        // Manual date input
        printf("                    \033[34mEnter the month (e.g., January):\033[0m ");
        scanf("%9s", month);  // Limits input to 9 characters
        printf("                    \033[34mEnter the date (e.g., 15):\033[0m ");
        scanf("%d", &date);
        printf("                    \033[34mEnter the year (e.g., 2023):\033[0m ");
        scanf("%d", &year);
    } else if (dateChoice == 2) {
        // Get current date automatically
        getCurrentDatei(month, &date, &year);
        printf("                    Using current date: \033[33m%s %d, %d\033[0m\n", month, date, year);
    } else {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }

    struct user_income_details data;


    FILE *f = fopen("Income_details.txt", "r");
    FILE *temp = fopen("Temp_income_details.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("                    \033[31mError opening file.\033[0m\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char fileUsername[50];
    struct user_income_details details;
    int edited = 0;

    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 &&
            strcmp(incomeName, details.name) == 0 &&
            strcmp(month, details.month) == 0 &&
            details.date == date && details.year == year) {
                printf("                    -----------------------------------------------------------\n");
                    printf("                    \033[1;32mIncome Name:\033[0m %s\n", details.name);
                    printf("                    \033[1;32mDescription:\033[0m %s\n", details.description);
                    printf("                    \033[1;32mAmount:\033[0m \033[32m%.2f\033[0m\n", details.amount);
                    printf("                    \033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                    printf("                    -----------------------------------------------------------\n");
                    printf("                    Is this the record you want to edit (1. Yes / 0. No) :");
                    int ch=0;
                    scanf("%d",&ch);
                    if (ch==0)
                    {
                        return;
                    }
                    struct user_income_details data;
    printf("                    \033[34mEnter the new name of the Income:\033[0m ");
    scanf(" %[^\n]s", data.name);
    printf("                    \033[34mEnter a new description for the Income:\033[0m ");
    scanf(" %[^\n]s", data.description);
    printf("                    \033[34mEnter the new amount:\033[0m ");
    scanf("%f", &data.amount);

    // Repeat date choice for the new entry
    printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                    Enter your choice: ");
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        printf("                    \033[34mEnter the month (e.g., January):\033[0m ");
        scanf("%9s", data.month);
        printf("                    \033[34mEnter the date (e.g., 15):\033[0m ");
        scanf("%d", &data.date);
        printf("                    \033[34mEnter the year (e.g., 2023):\033[0m ");
        scanf("%d", &data.year);
    } else if (dateChoice == 2) {
        getCurrentDatei(data.month, &data.date, &data.year);
        printf("                    Using current date: \033[33m%s %d, %d\033[0m\n", data.month, data.date, data.year);
    } else {
        printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
        return;
    }
            edited = 1;  // Mark the income as found
        } else {
            fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                    fileUsername, details.name, details.description,
                    details.amount, details.month, details.date, details.year);
        }
    }

    fclose(f);

    if (edited) {
        fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                username, data.name, data.description,
                data.amount, data.month, data.date, data.year);
        printf("                    \033[32mIncome edited successfully.\033[0m\n");
    } else {
        printf("                    \033[31mNo matching income found for editing.\033[0m\n");
    }

    fclose(temp);
    remove("Income_details.txt");
    rename("Temp_income_details.txt", "Income_details.txt");
}

void viewIncome(char *username) {
    
    FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("                    \033[31mError opening file.\033[0m\n");
        return;
    }

    struct user_income_details details;
    char fileUsername[50];
    int found = 0;

    printf("                    Income details for \033[33m%s\033[0m:\n", username);
    printf("                    -----------------------------------------------------------\n");
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            printf("                    \033[1;32mIncome Name:\033[0m %s\n", details.name);
            printf("                    \033[1;32mDescription:\033[0m %s\n", details.description);
            printf("                    \033[1;32mAmount:\033[0m \033[32m%.2f\033[0m\n", details.amount);
            printf("                    \033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
            printf("                    -----------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("                    \033[31mNo income records found.\033[0m\n");
        printf("                    -----------------------------------------------------------\n");
    }
    
    fclose(f);


}

void monthlyIncome(char *username) {

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
        float totalinc = 0;
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
            getCurrentDatei(monthcheck, &date, &yearcheck);
            printf("                    Using current Month: %s %d\n", monthcheck, yearcheck);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }
        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s viewed monthly income statement for month %s, %d on %02d %s, %04d at %02d:%02d:%02d\n",username,monthcheck,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);

        FILE *f = fopen("Income_details.txt", "r");
        if (f == NULL) {
            printf("                    \033[31mError opening file.\033[0m\n");
            return;
        }

        char fileUsername[50];
        struct user_income_details details;
        int found = 0;

        printf("\n                    Income statements for user: \033[1;33m%s\033[0m\n", username);
        printf("                    -----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && yearcheck == details.year && strcmp(monthcheck, details.month) == 0) {
                found = 1;
                totalinc += details.amount;
                printf("                    Name: %s\n", details.name);
                printf("                    Description: %s\n", details.description);
                printf("                    Amount: \033[32m%.2f\033[0m\n", details.amount);
                printf("                    Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        fclose(f);

        if (found) {
            printf("                    The total monthly Income for %s in %s %d is: \033[32m%.2f\033[0m\n", username, monthcheck, yearcheck, totalinc);
        } else {
            printf("                    No Income found for user %s in %s %d\n", username, monthcheck, yearcheck);
        }

 
}

void yearlyIncome(char *username) {

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

        int yearcheck;
        char monthcheck[10];
        int date;
        float totalinc = 0;

        printf("                    Would you like to:\n                    1. Enter the Year manually\n                    2. Use the current Year\n                    Enter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            
            
            printf("                    \033[34mEnter the year (e.g., 2023):\033[0m ");
            scanf("%d", &yearcheck);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDatei(monthcheck, &date, &yearcheck);
            printf("                    Using current Year: %d\n", yearcheck);
        } else {
            printf("                    \033[31mInvalid choice. Please try again.\033[0m\n");
            return;
        }

        FILE *f = fopen("Income_details.txt", "r");
        if (f == NULL) {
            printf("                    \033[31mError opening file.\033[0m\n");
            return;
        }

        logf=fopen("log.txt","a");
        fprintf(logf,"User : %s yearly income statement for year %d on %02d %s, %04d at %02d:%02d:%02d\n",username,yearcheck,day, monthNames[month], year, hour, minute, second);
        fclose(logf);

        char fileUsername[50];
        struct user_income_details details;
        int found = 0;

        printf("\n                    Income statements for user: \033[1;33m%s\033[0m\n", username);
        printf("                    -----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && yearcheck == details.year) {
                found = 1;
                totalinc += details.amount;
                printf("                    \033[1;32mName:\033[0m %s\n", details.name);
                printf("                    \033[1;32mDescription:\033[0m %s\n", details.description);
                printf("                    \033[1;32mAmount:\033[0m %.2f\n", details.amount);
                printf("                    \033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        fclose(f);

        if (found) {
            printf("                    The total Yearly Income for %s in %d is: \033[32m%.2f\033[0m\n", username, yearcheck, totalinc);
        } else {
            printf("                    No expenses found for user %s in %d\n", username, yearcheck);
        }

        
}


