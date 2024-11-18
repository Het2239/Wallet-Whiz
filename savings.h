// expense_manager.h

#ifndef SAVINGS_H
#define SAVINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for expense details
struct expense_details {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category;
};

// Define the Node structure for linked list
struct node {
    struct expense_details s;
    struct node *next;
};

// Declare the global head pointer for the linked list
extern struct node *heaD;

// Function prototype for the savings function
void savings(char *username);

#endif // EXPENSE_MANAGER_H
