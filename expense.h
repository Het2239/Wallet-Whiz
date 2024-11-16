#ifndef EXPENSE_H
#define EXPENSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Structure to store user expense details
struct user_expense_details {
    char name[50];           // Name of the expense
    float amount;            // Amount spent
    char description[100];   // Description of the expense
    char month[10];          // Month of the expense
    int date;                // Date of the expense
    int year;                // Year of the expense
    char category;           // Category of the expense (U, H, S, P, O)
};

// Function to get the current date (month, day, year)
void getCurrentDate(char *month, int *day, int *year);

// Function to enter a new expense
void enterExpense(char *username);

// Function to read and display the user's expenses
void readExpense(char *username);

// Function to delete a specific expense
void deleteExpense(char *username);

// Function to edit an existing expense
void editExpense(char *username);

// Function to view expenses by category
void expenseOnCategory(char *username);

// Function to calculate and display the total monthly expense
void totalmonthlyExpense(char *username);

// Function to calculate and display the total yearly expense
void totalyearlyExpense(char *username);

#endif // EXPENSE_TRACKER_H
