#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user_income_details
{
    char name[50];
    char description[100];
    float amount;
    char month[10];
    int date;
    int year;
}details;

void addIncome(char *username, struct user_income_details *details){

    int flag=0;
    do
    {
        system("clear");

        FILE *f = fopen("Income_details.txt", "a");
    if (f == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    printf("Enter the name of the expense: ");
    scanf(" %[^\n]s", details->name);
    printf("Enter a description for the Income: ");
    scanf(" %[^\n]s", details->description); // Reads input with spaces
    printf("Enter the amount: ");
    scanf("%f", &details->amount);
    printf("Enter the month (e.g., January): ");
    scanf("%s", details->month);
    printf("Enter the date (e.g., 15): ");
    scanf("%d", &details->date);
    printf("Enter the year (e.g., 2023): ");
    scanf("%d", &details->year);

    // Write the details to the file in comma and space separated format
    fprintf(f, "%s, %s, %s, %.2f, %s, %d, %d\n", 
            username, details->name, details->description,
            details->amount, details->month, details->date, details->year);

    fclose(f);
    printf("Income recorded successfully.\n");


        printf("\n1. Run again\n");
        printf("0. Exit\n");
        int choice=0;
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:
            flag=1;
            break;
        case 0:
            flag=0;
            break;
        
        }
    } while (flag==1);

    
}

void deleteIncome(char *username){

    int flag=0;
    do
    {
        system("clear");

        char incomeName[50];
    char month[10];
    int date, year;

    // Take input for expense name, month, date, and year to identify which record to delete
    printf("Enter the name of the Income to delete: ");
    scanf(" %[^\n]s", incomeName);
    printf("Enter the month of the expense to delete (e.g., January): ");
    scanf("%s", month);
    printf("Enter the date of the expense to delete (e.g., 15): ");
    scanf("%d", &date);
    printf("Enter the year of the expense to delete (e.g., 2024): ");
    scanf("%d", &year);

    FILE *f = fopen("Income_details.txt", "r");
    FILE *temp = fopen("Temp_income_details.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details details;
    int deleted = 0;

    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        // Check if the current record matches the input criteria for deletion
        if (strcmp(username, fileUsername) == 0 &&
            strcmp(incomeName, details.name) == 0 &&
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
    fclose(temp);

    // Replace the original file with the updated file if deletion was successful
    if (deleted) {
        remove("Income_details.txt");
        rename("Temp_income_details.txt", "Income_details.txt");
        printf("Expense deleted successfully.\n");
    } else {
        remove("Temp_income_details.txt");
        printf("No matching expense found for deletion.\n");
    }


        printf("\n1. Run again\n");
        printf("0. Exit\n");
        int choice=0;
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:
            flag=1;
            break;
        case 0:
            flag=0;
            break;
        
        }
    } while (flag==1);

    
}

void editIncome(char *username){

    int flag=0;
    do
    {
        system("clear");

        char incomeName[50];
    char month[10];
    int date, year;

    // Take input for expense name, month, date, and year to identify which record to delete
    printf("Enter the name of the Income to edit: ");
    scanf(" %[^\n]s", incomeName);
    printf("Enter the month of the income to edit (e.g., January): ");
    scanf("%s", month);
    printf("Enter the date of the income to edit (e.g., 15): ");
    scanf("%d", &date);
    printf("Enter the year of the income to edit (e.g., 2024): ");
    scanf("%d", &year);

    struct user_income_details data;
    printf("Enter the new name of the Income: ");
    scanf(" %[^\n]s", data.name);
    printf("Enter a new description for the Income: ");
    scanf(" %[^\n]s", data.description); // Reads input with spaces
    printf("Enter the new amount: ");
    scanf("%f", &data.amount);
    printf("Enter the new month (e.g., January): ");
    scanf("%s", data.month);
    printf("Enter the new date (e.g., 15): ");
    scanf("%d", &data.date);
    printf("Enter the new year (e.g., 2023): ");
    scanf("%d", &data.year);

    FILE *f = fopen("Income_details.txt", "r");
    FILE *temp = fopen("Temp_income_details.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details details;
    int deleted = 0;

    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        // Check if the current record matches the input criteria for deletion
        if (strcmp(username, fileUsername) == 0 &&
            strcmp(incomeName, details.name) == 0 &&
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
        remove("Income_details.txt");
        rename("Temp_income_details.txt", "Income_details.txt");
        printf("Income Edited successfully.\n");
    } else {
        remove("Temp_income_details.txt");
        printf("No matching income found to edit.\n");
    }


        printf("\n1. Run again\n");
        printf("0. Exit\n");
        int choice=0;
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:
            flag=1;
            break;
        case 0:
            flag=0;
            break;
        
        }
    } while (flag==1);

    
    
}

void viewIncome(char *username){

    int flag=0;
    do
    {
        system("clear");
        FILE *f = fopen("Income_details.txt", "r");
    if (f == NULL) {
        printf("Error opening file for reading or file does not exist.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details details;
    int found = 0;

    printf("\nIncome statements for user: %s\n", username);
    printf("-----------------------------------------------------------\n");

    // Reading data with comma and space separation
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n", 
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            found = 1;
            
            printf("Income Name: %s\n", details.name);
            printf("Description: %s\n", details.description);
            printf("Amount: %.2f\n", details.amount);
            printf("Date: %s %d, %d\n", details.month, details.date, details.year);
            printf("-----------------------------------------------------------\n");
        }
    }

    if (!found) {
        printf("No income statements found for user: %s\n", username);
    }

    fclose(f);


        printf("\n1. Run again\n");
        printf("0. Exit\n");
        int choice=0;
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:
            flag=1;
            break;
        case 0:
            flag=0;
            break;
        
        }
    } while (flag==1);

    
}

void monthlyIncome(char *username){
    int flag=0;
    do
    {
        system("clear");
        char monthcheck[10];
    int yearcheck;
    float totalinc=0;

    printf("Enter the month to view your income statement(eg. January) : ");
    scanf("%s",monthcheck);
    printf("Enter the year t0 check your monthly income statement(eg. 2024) : ");
    scanf("%d",&yearcheck);

    FILE *f = fopen("Income_details.txt", "r");
    
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char fileUsername[50];
    struct user_income_details details;
    int found = 0;

    printf("\nIncome statements for user: %s\n", username);
    printf("-----------------------------------------------------------\n");

    // Reading data with comma and space separation
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n", 
                  fileUsername, details.name, details.description,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && yearcheck ==details.year && strcmp(monthcheck,details.month)==0) {
            found = 1;
            totalinc+=details.amount;
            printf("Name: %s\n", details.name);
            printf("Description: %s\n", details.description);
            
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
    else{
        printf("Total Monthly Income : %.2f\n",totalinc);
        printf("-----------------------------------------------------------\n");
    }
}


        printf("\n1. Run again\n");
        printf("0. Exit\n");
        int choice=0;
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:
            flag=1;
            break;
        case 0:
            flag=0;
            break;
        
        }
    } while (flag==1);

    

}

void yearlyIncome(char *username){
    int flag=0;

    do
    {
    system("clear");
    int yearcheck;
    float totalinc=0;
    
    printf("Enter the year t0 check your monthly income statement(eg. 2024) : ");
    scanf("%d",&yearcheck);

    FILE *f = fopen("Income_details.txt", "r");
    
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }


    char fileUsername[50];
    struct user_income_details details;
    int found = 0;

    printf("\nIncome statements for user: %s\n", username);
    printf("-----------------------------------------------------------\n");

    // Reading data with comma and space separation
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %f, %9[^,], %d, %d\n", 
                  fileUsername, details.name, details.description, 
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && yearcheck ==details.year ) {
            found = 1;
            totalinc+=details.amount;
            printf("\033[1;32mName:\033[0m %s\n", details.name);
            printf("\033[1;32mDescription:\033[0m %s\n", details.description);
            
            printf("\033[1;32mAmount:\033[0m %.2f\n", details.amount);
            printf("\033[1;32mDate:\033[0m %s %d, %d\n", details.month, details.date, details.year);
            printf("-----------------------------------------------------------\n");

    
        
    fclose(f);
    }
    if (found != 1)
    {
        printf("No Record found\n");
        printf("-----------------------------------------------------------\n");
    }
    else{
        printf("Total Yearly Income : %.2f\n",totalinc);
        printf("-----------------------------------------------------------\n");
    }
                  }
    printf("\n1. Run again\n");
    printf("0. Exit\n");
    int choice=0;
    printf("Enter your choice : ");
    scanf("%d",&choice);
    
    switch (choice)
    {
    case 1:
        flag=1;
        break;
    case 0:
        flag=0;
        break;
    
    }
    
    } while (flag == 1);
    
    
}

int main(){
    struct user_income_details expense;
    char username[100]; // Increased size for username to support longer inputs

    printf("Enter your username to read your expenses: ");
    fgets(username, sizeof(username), stdin); // Use fgets to safely read the username
    username[strcspn(username, "\n")] = 0;  // Remove the trailing newline character from fgets
    // addIncome(username,&expense); //
    viewIncome(username);
    // monthlyIncome(username);
    // yearlyIncome(username);
    // editIncome(username);        
    // deleteIncome(username);
}