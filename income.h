#ifndef INCOME_H
#define INCOME_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Structure to store user's income details
struct user_income_details {
    char name[50];
    char description[100];
    float amount;
    char month[10];
    int date;
    int year;
};

// Function prototypes

// Function to get the current date (month, day, year)
void getCurrentDate(char *month, int *day, int *year);

// Function to add a new income entry
void addIncome(char *username);

// Function to delete an income entry
void deleteIncome(char *username);

// Function to edit an existing income entry
void editIncome(char *username);

// Function to view all income entries for a specific user
void viewIncome(char *username);

// Function to view the monthly income statement for a specific user
void monthlyIncome(char *username);

// Function to view the yearly income statement for a specific user
void yearlyIncome(char *username);

#endif // INCOME_MANAGER_H
