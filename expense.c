#include <stdio.h>
#include <string.h>

struct user_expense_details {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category; 
} details;




void enterExpense(char *username, struct user_expense_details *details) {
    FILE *f = fopen("Expense_details.txt", "a");
    if (f == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    printf("Enter the name of the expense: ");
    scanf(" %[^\n]s", details->name); // Reads input with spaces
    printf("Enter a description for the expense: ");
    scanf(" %[^\n]s", details->description); // Reads input with spaces
    printf("Enter the category (U, H, S, P, O): ");
    scanf(" %c", &details->category); // Ensure leading space to read a single character correctly
    printf("Enter the amount: ");
    scanf("%f", &details->amount);
    printf("Enter the month (e.g., January): ");
    scanf("%s", details->month);
    printf("Enter the date (e.g., 15): ");
    scanf("%d", &details->date);
    printf("Enter the year (e.g., 2023): ");
    scanf("%d", &details->year);

    // Write the details to the file in comma and space separated format
    fprintf(f, "%s, %s, %s, %c, %.2f, %s, %d, %d\n", 
            username, details->name, details->description, details->category,
            details->amount, details->month, details->date, details->year);

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

void expenseOnCategory(char *username){
    char cat;
    printf("Enter the category of expense you want to view (U, H, S, P, O): ");
    scanf("%c", &cat);

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
    fclose(f);
    }
}
}

void editExpense(char *username){
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
    printf("Enter the new month (e.g., January): ");
    scanf("%s", data.month);
    printf("Enter the new date (e.g., 15): ");
    scanf("%d", &data.date);
    printf("Enter the new year (e.g., 2023): ");
    scanf("%d", &data.year);

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

void savings(char *username){

}

void totalmonthlyExpense(char *username){
    char monthcheck[10];
    int yearcheck;

    printf("Enter the month to view your expense statement(eg. January) : ");
    scanf("%s",monthcheck);
    printf("Enter the year t0 check your monthly expense statement(eg. 2024) : ");
    scanf("%d",&yearcheck);

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
        if (strcmp(username, fileUsername) == 0 && yearcheck ==details.year && strcmp(monthcheck,details.month)==0) {
            found = 1;
            printf("Name: %s\n", details.name);
            printf("Description: %s\n", details.description);
            printf("Category: %c\n", details.category);
            printf("Amount: %.2f\n", details.amount);
            printf("Date: %s %d, %d\n", details.month, details.date, details.year);
            printf("-----------------------------------------------------------\n");

    
        
    fclose(f);
    }
    if (found != 1)
    {
        printf("No Record found\n");
        printf("-----------------------------------------------------------\n");
    }
}
}

void totalyearlyExpense(char *username){
    
    int yearcheck;

    
    printf("Enter the year t0 check your monthly expense statement(eg. 2024) : ");
    scanf("%d",&yearcheck);

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
        if (strcmp(username, fileUsername) == 0 && yearcheck ==details.year ) {
            found = 1;
            printf("Name: %s\n", details.name);
            printf("Description: %s\n", details.description);
            printf("Category: %c\n", details.category);
            printf("Amount: %.2f\n", details.amount);
            printf("Date: %s %d, %d\n", details.month, details.date, details.year);
            printf("-----------------------------------------------------------\n");

    
        
    fclose(f);
    }
    if (found != 1)
    {
        printf("No Record found\n");
        printf("-----------------------------------------------------------\n");
    }
}
}

int main() {
    struct user_expense_details expense;
    char username[100]; 

    printf("Enter your username to read your expenses: ");
    fgets(username, sizeof(username), stdin); 
    username[strcspn(username, "\n")] = 0;  
    enterExpense(username,&expense);
    readExpense(username);
    // deleteExpense(username);
    // expenseOnCategory(username);
    // totalmonthlyExpense(username);
    // totalyearlyExpense(username);
    // enterExpense(username, &expense);

    return 0;
}
