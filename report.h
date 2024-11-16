#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>

// Structure definitions
struct user_income_details {
    char name[50];
    char description[100];
    float amount;
    char month[10];
    int date;
    int year;
};

struct user_expense_details {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category;
};

// Function prototypes
void getCurrentDate(char *month, int *day, int *year);
void monthlyexpenseReport(char *username);
void yearlyexpenseReport(char *username);

#endif // EXPENSE_REPORT_H
