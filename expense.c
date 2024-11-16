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
            printf("Error opening file for writing.\n");
            return;
        }

        struct user_expense_details details;
        printf("Enter the name of the expense: ");
        scanf(" %[^\n]s", details.name); // Reads input with spaces
        printf("Enter a description for the expense: ");
        scanf(" %[^\n]s", details.description); // Reads input with spaces
        printf("Enter the category (U, H, S, P, O): ");
        scanf(" %c", &details.category); // Ensure leading space to read a single character correctly
        printf("Enter the amount: ");
        scanf("%f", &details.amount);

        printf("Would you like to:\n1. Enter the date manually\n2. Use the current date\nEnter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("Enter the month (e.g., January): ");
            scanf("%s", details.month);
            printf("Enter the date (e.g., 15): ");
            scanf("%d", &details.date);
            printf("Enter the year (e.g., 2023): ");
            scanf("%d", &details.year);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(details.month, &details.date, &details.year);
            printf("Using current date: %s %d, %d\n", details.month, details.date, details.year);
        } else {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        // Write the details to the file in comma and space separated format
        fprintf(f, "%s, %s, %s, %c, %.2f, %s, %d, %d\n",
                username, details.name, details.description, details.category,
                details.amount, details.month, details.date, details.year);

        fclose(f);
        printf("Expense recorded successfully.\n");

       
}

void readExpense(char *username) {
    

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("Error opening file for reading or file does not exist.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\nExpenses for user: %s\n", username);
        printf("-----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0) {
                found = 1;
                printf("Name: %s\n", details.name);
                printf("Description: %s\n", details.description);
                printf("Category: %c\n", details.category);
                printf("Amount: %.2f\n", details.amount);
                printf("Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("-----------------------------------------------------------\n");
            }
        }

        if (!found) {
            printf("No expenses found for user: %s\n", username);
        }

        fclose(f);

        
}

void deleteExpense(char *username) {
    

        char expenseName[50];
        char month[10];
        int date, year;

        // Take input for expense name, month, date, and year to identify which record to delete
        printf("Enter the name of the expense to delete: ");
        scanf(" %[^\n]s", expenseName);
        printf("Enter the month of the expense to delete (e.g., January): ");
        scanf("%s", month);
        printf("Enter the date of the expense to delete (e.g., 15): ");
        scanf("%d", &date);
        printf("Enter the year of the expense to delete (e.g., 2024): ");
        scanf("%d", &year);

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
            printf("Expense deleted successfully.\n");
        } else {
            remove("Temp_expense_details.txt");
            printf("No matching expense found for deletion.\n");
        }

        
}

void editExpense(char *username) {
    

        char expenseName[50];
        char month[10];
        int date, year;

        // Take input for expense name, month, date, and year to identify which record to delete
        printf("Enter the name of the expense to edit: ");
        scanf(" %[^\n]s", expenseName);
        printf("Enter the month of the expense to edit (e.g., January): ");
        scanf("%s", month);
        printf("Enter the date of the expense to edit (e.g., 15): ");
        scanf("%d", &date);
        printf("Enter the year of the expense to edit (e.g., 2024): ");
        scanf("%d", &year);

        struct user_expense_details data;
        printf("Enter the new name of the Expense: ");
        scanf(" %[^\n]s", data.name);
        printf("Enter a new description for the Expense: ");
        scanf(" %[^\n]s", data.description); // Reads input with spaces
        printf("Enter the new amount: ");
        scanf("%f", &data.amount);

        printf("Would you like to:\n1. Enter the new date manually\n2. Use the current date\nEnter your choice : ");
        int dateChoice;
        scanf("%d", &dateChoice);

        if (dateChoice == 1) {
            // Manual date input
            printf("Enter the month (e.g., January): ");
            scanf("%s", data.month);
            printf("Enter the date (e.g., 15): ");
            scanf("%d", &data.date);
            printf("Enter the year (e.g., 2023): ");
            scanf("%d", &data.year);
        } else if (dateChoice == 2) {
            // Get current date automatically
            getCurrentDate(data.month, &data.date, &data.year);
            printf("Using current date: %s %d, %d\n", data.month, data.date, data.year);
        } else {
            printf("Invalid choice. Please try again.\n");
            continue;
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

        while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            // Check if the current record matches the input criteria for deletion
            if (strcmp(username, fileUsername) == 0 &&
                strcmp(expenseName, details.name) == 0 &&
                strcmp(month, details.month) == 0 &&
                details.date == date && details.year == year) {
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
            fprintf(temp, "%s, %s, %s, %.2f, %s, %d, %d\n",
                    username, data.name, data.description,
                    data.amount, data.month, data.date, data.year);
            fclose(temp);
            remove("Expense_details.txt");
            rename("Temp_expense_details.txt", "Expense_details.txt");
            printf("Expense Edited successfully.\n");
        } else {
            remove("Temp_expense_details.txt");
            printf("No matching expense found to edit.\n");
        }

        
}


void expenseOnCategory(char *username) {
    

        char cat;
        printf("Enter the category of expense you want to view (U, H, S, P, O): ");
        scanf(" %c", &cat);

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\nExpenses for user: %s\n", username);
        printf("-----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && cat == details.category) {
                found = 1;
                printf("Name: %s\n", details.name);
                printf("Description: %s\n", details.description);
                printf("Category: %c\n", details.category);
                printf("Amount: %.2f\n", details.amount);
                printf("Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("-----------------------------------------------------------\n");
            }
        }

        if (!found) {
            printf("No expenses found for category %c for user: %s\n", cat, username);
        }

        fclose(f);

        
}

void totalmonthlyExpense(char *username) {
    

        char monthcheck[10];
        int yearcheck;
        float totalexp = 0;

        printf("Enter the month for which you want to see the total expense (e.g., January): ");
        scanf("%s", monthcheck);
        printf("Enter the year for which you want to see the total expense (e.g., 2023): ");
        scanf("%d", &yearcheck);

        FILE *f = fopen("Expense_details.txt", "r");
        if (f == NULL) {
            printf("Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                      fileUsername, details.name, details.description, &details.category,
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(monthcheck, details.month) == 0 && yearcheck == details.year) {
                printf("Name: %s\n", details.name);
                printf("Description: %s\n", details.description);
                printf("Category: %c\n", details.category);
                printf("Amount: %.2f\n", details.amount);
                printf("Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("-----------------------------------------------------------\n");
                totalexp += details.amount;
                found = 1;
            }
        }

        fclose(f);

        if (found) {
            printf("The total monthly expense for %s in %s %d is: %.2f\n", username, monthcheck, yearcheck, totalexp);
        } else {
            printf("No expenses found for user %s in %s %d\n", username, monthcheck, yearcheck);
        }

        
}

void totalyearlyExpense(char *username) {
    

        int yearcheck;
        float totalexp = 0;

        printf("Enter the year to check your monthly expense statement (e.g., 2024): ");
        scanf("%d", &yearcheck);

        FILE *f = fopen("Expense_details.txt", "r");

        if (f == NULL) {
            printf("Error opening file.\n");
            return;
        }

        char fileUsername[50];
        struct user_expense_details details;
        int found = 0;

        printf("\nExpense statements for user: %s\n", username);
        printf("-----------------------------------------------------------\n");

        // Reading data with comma and space separation
        while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n", 
                      fileUsername, details.name, details.description, &details.category, 
                      &details.amount, details.month, &details.date, &details.year) != EOF) {
            if (strcmp(username, fileUsername) == 0 && yearcheck == details.year) {
                found = 1;
                totalexp += details.amount;
                printf("Name: %s\n", details.name);
                printf("Description: %s\n", details.description);
                printf("Category: %c\n", details.category);
                printf("Amount: %.2f\n", details.amount);
                printf("Date: %s %d, %d\n", details.month, details.date, details.year);
                printf("-----------------------------------------------------------\n");
            }
        }

        fclose(f);

        if (found != 1) {
            printf("No record found\n");
            printf("-----------------------------------------------------------\n");
        } else {
            printf("Total Yearly Expense: %.2f\n", totalexp);
            printf("-----------------------------------------------------------\n");
        }

        
}


// int main() {
//     char username[50];
//     printf("Enter your username: ");
//     scanf("%s", username);

//     int choice;
//     do {
//         system("clear");
//         printf("\nExpense Tracker Menu:\n");
//         printf("1. Enter Expense\n");
//         printf("2. Read Expense\n");
//         printf("3. Delete Expense\n");
//         printf("4. Edit Expense\n");
//         printf("5. View Expense by Category\n");
//         printf("6. View Total Monthly Expense\n");
//         printf("7. View Total Yearly Expense\n");
//         printf("0. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);

//         switch (choice) {
//             case 1:
//                 enterExpense(username);
//                 break;
//             case 2:
//                 readExpense(username);
//                 break;
//             case 3:
//                 deleteExpense(username);
//                 break;
//             case 4:
//                 deleteExpense(username);
//                 break;
//             case 5:
//                 expenseOnCategory(username);
//                 break;
//             case 6:
//                 totalmonthlyExpense(username);
//                 break;
//             case 7:
//                 totalyearlyExpense(username);
//                 break;
//             case 0:
//                 printf("Exiting the program.\n");
//                 break;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//                 break;
//         }
        
//     } while (choice != 0);

//     return 0;
// }
