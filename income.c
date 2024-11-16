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
        printf("                    Error opening file for writing.\n");
        return;
    }

    printf("                    Enter the name of the Income: ");
    scanf(" %[^\n]s", detail.name);
    printf("                    Enter a description for the Income: ");
    scanf(" %[^\n]s", detail.description); // Reads input with spaces
    printf("                    Enter the amount: ");
    scanf("%f", &detail.amount);

    printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                   Enter your choice : ");
    int dateChoice;
    scanf("%d", &dateChoice);

    if (dateChoice == 1) {
        // Manual date input
        printf("                    Enter the month (e.g., January): ");
        scanf("%s", detail.month);
        printf("                    Enter the date (e.g., 15): ");
        scanf("%d", &detail.date);
        printf("                    Enter the year (e.g., 2023): ");
        scanf("%d", &detail.year);
    } else if (dateChoice == 2) {
        // Get current date automatically
        getCurrentDatei(detail.month, &detail.date, &detail.year);
        printf("                    Using current date: %s %d, %d\n", detail.month, detail.date, detail.year);
    } else {
        printf("                    Invalid choice. Please try again.\n");
        return;
    }

    // Write the details to the file in comma and space-separated format
    fprintf(f, "%s, %s, %s, %.2f, %s, %d, %d\n",
            username, detail.name, detail.description,
            detail.amount, detail.month, detail.date, detail.year);

    fclose(f);
    printf("                    Income recorded successfully.\n");

    
}

void deleteIncome(char *username) {
    

        char incomeName[50];
        char month[10];
        int date, year;

        printf("                    Enter the name of the Income to delete: ");
        scanf(" %[^\n]s", incomeName);

        printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n");
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
            getCurrentDatei(month, &date, &year);
            printf("                    Using current date: %s %d, %d\n", month, date, year);
        } else {
            printf("                    Invalid choice. Please try again.\n");
            return;
        }

        FILE *f = fopen("Income_details.txt", "r");
        FILE *temp = fopen("Temp_income_details.txt", "w");
        if (f == NULL || temp == NULL) {
            printf("                    Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_income_details details;
        int deleted = 0;

        while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 &&
                strcmp(incomeName, details.name) == 0 &&
                strcmp(month, details.month) == 0 &&
                details.date == date && details.year == year) {
                deleted = 1; // Mark the income as found and delete it by not writing to the temp file
            } else {
                fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                        fileUsername, details.name, details.description,
                        details.amount, details.month, details.date, details.year);
            }
        }

        fclose(f);
        fclose(temp);

        if (deleted) {
            remove("Income_details.txt");
            rename("Temp_income_details.txt", "Income_details.txt");
            printf("                    Income deleted successfully.\n");
        } else {
            remove("Temp_income_details.txt");
            printf("                    No matching income found for deletion.\n");
        }

        
}

void editIncome(char *username) {
    

        char incomeName[50];
        char month[10];
        int date, year;

        printf("                    Enter the name of the Income to edit: ");
        scanf(" %[^\n]s", incomeName);

        printf("                    Would you like to:\n                    1. Enter the date manually\n                    2. Use the current date\n                   Enter your choise :");
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
            getCurrentDatei(month, &date, &year);
            printf("                    Using current date: %s %d, %d\n", month, date, year);
        } else {
            printf("                    Invalid choice. Please try again.\n");
            return;
        }

        struct user_income_details data;
        printf("                    Enter the new name of the Income: ");
        scanf(" %[^\n]s", data.name);
        printf("                    Enter a new description for the Income: ");
        scanf(" %[^\n]s", data.description);
        printf("                    Enter the new amount: ");
        scanf("%f", &data.amount);
        printf("                    Enter the new month (e.g., January): ");
        scanf("%s", data.month);
        printf("                    Enter the new date (e.g., 15): ");
        scanf("%d", &data.date);
        printf("                    Enter the new year (e.g., 2023): ");
        scanf("%d", &data.year);

        FILE *f = fopen("Income_details.txt", "r");
        FILE *temp = fopen("Temp_income_details.txt", "w");
        if (f == NULL || temp == NULL) {
            printf("                    Error opening file.\n");
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
                edited = 1; // Mark the income as found
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
            printf("                    Income edited successfully.\n");
        } else {
            printf("                    No matching income found for editing.\n");
        }

        fclose(temp);
        remove("Income_details.txt");
        rename("Temp_income_details.txt", "Income_details.txt");

  
}

void viewIncome(char *username) {
    
    FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("                    Error opening file.\n");
        return;
    }

    struct user_income_details details;
    char fileUsername[50];
    int found = 0;

    printf("                    Income details for %s:\n", username);
    printf("                    -----------------------------------------------------------\n");
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            printf("                    Income Name: %s\n", details.name);
            printf("                    Description: %s\n", details.description);
            printf("                    Amount: %.2f\n", details.amount);
            printf("                    Date: %s %d, %d\n", details.month, details.date, details.year);
            printf("                    -----------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("                    No income records found.\n");
        printf("                    -----------------------------------------------------------\n");
    }
    
    fclose(f);

    // printf("\nPress Enter to continue...");
    // getchar(); // Wait for user input to continue
    // getchar(); // Handle newline from previous input
}

void monthlyIncome(char *username) {
    
        char monthcheck[10];
        int yearcheck;
        float totalinc = 0;

        printf("                    Enter the month to view your income statement (e.g., January): ");
        scanf("%s", monthcheck);
        printf("                    Enter the year to check your monthly income statement (e.g., 2024): ");
        scanf("%d", &yearcheck);

        FILE *f = fopen("Income_details.txt", "r");
        if (f == NULL) {
            printf("                    Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_income_details details;
        int found = 0;

        printf("\n                    Income statements for user: %s\n", username);
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
                printf("                    Amount: %.2f\n", details.amount);
                printf("                    Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("                    -----------------------------------------------------------\n");
            }
        }

        fclose(f);

        if (found != 1) {
            printf("                    No Record found\n");
            printf("                    -----------------------------------------------------------\n");
        } else {
            printf("                    Total Monthly Income: %.2f\n", totalinc);
            printf("                    -----------------------------------------------------------\n");
        }

 
}

void yearlyIncome(char *username) {
    
        int yearcheck;
        float totalinc = 0;

        printf("                    Enter the year to check your yearly income statement (e.g., 2024): ");
        scanf("%d", &yearcheck);

        FILE *f = fopen("Income_details.txt", "r");
        if (f == NULL) {
            printf("                    Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_income_details details;
        int found = 0;

        printf("\n                    Income statements for user: %s\n", username);
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

        if (found != 1) {
            printf("                    No Record found\n");
            printf("                    -----------------------------------------------------------\n");
        } else {
            printf("                    Total Yearly Income: %.2f\n", totalinc);
            printf("                    -----------------------------------------------------------\n");
        }

        
}


// int main() {
//     // Example usage
//     char username[50];
//     printf("Enter your username: ");
//     scanf("%s", username);

    
//     int option;

//     do {
//         printf("\nMenu:\n");
//         printf("1. Add Income\n");
//         printf("2. Delete Income\n");
//         printf("3. Edit Income\n");
//         printf("4. View Income\n");
//         printf("5. View monthly Income statement\n");
//         printf("6. View yearly Income statement\n");
//         printf("0. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &option);

//         switch (option) {
//             case 1:
//                 addIncome(username);
//                 break;
//             case 2:
//                 deleteIncome(username);
//                 break;
//             case 3:
//                 editIncome(username);
//                 break;
//             case 4:
//                 viewIncome(username);
//                 break;
//             case 5:
//                 monthlyIncome(username);
//                 break;
//             case 6:
//                 yearlyIncome(username);
//                 break;
//             case 0:
//                 printf("Exiting...\n");
//                 break;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//                 break;
//         }
//     } while (option != 0);

//     return 0;
// }
