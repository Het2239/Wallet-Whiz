#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct definitions as they were in the .h file
struct expense_details {
    char name[50];
    float amount;
    char description[100];
    char month[10];
    int date;
    int year;
    char category;
};

struct node {
    struct expense_details s;
    struct node *next;
};

struct node *heaD = NULL;

void savings(char *username) {
    FILE *f = fopen("Expense_details.txt", "r"); // Adjust file path as needed
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char cat = 'S'; // Specify the category for filtering
    char fileUsername[50];
    struct expense_details details;
    int found = 0;
    float totalsave=0.0;

    printf("\n                    Savings for user: \033[1;33m%s\033[0m\n", username);
    printf("                    -----------------------------------------------------------\n");

    // Read data from the file
    while (fscanf(f, "%[^,], %49[^,], %99[^,], %c, %f, %9[^,], %d, %d\n",
                  fileUsername, details.name, details.description, &details.category,
                  &details.amount, details.month, &details.date, &details.year) != EOF) {
        if (strcmp(username, fileUsername) == 0 && cat == details.category) {
            struct node *newnode = (struct node *)malloc(sizeof(struct node));
            if (newnode == NULL) {
                printf("Memory allocation failed.\n");
                fclose(f);
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
            newnode->next = NULL; // Ensure the new node points to NULL
            totalsave+=details.amount;

            // Insert at the end of the list
            if (heaD == NULL) {
                heaD = newnode;
            } else {
                struct node *buffernode = heaD;
                while (buffernode->next != NULL) {
                    buffernode = buffernode->next;
                }
                buffernode->next = newnode;
            }

            found = 1;
        }
    }

    if (found) {
        struct node *buffernode = heaD;
        while (buffernode != NULL) {
            printf("                    \033[1;31mName:\033[0m %s\n", buffernode->s.name);
            printf("                    \033[1;31mDescription:\033[0m %s\n", buffernode->s.description);
            printf("                    \033[1;31mCategory:\033[0m %c\n", buffernode->s.category);
            printf("                    \033[1;31mAmount:\033[0m \033[31m%.2f\033[0m\n", buffernode->s.amount);
            printf("                    \033[1;31mDate:\033[0m %s %d, %d\n", buffernode->s.month, buffernode->s.date, buffernode->s.year);
            printf("                    -----------------------------------------------------------\n");
            buffernode = buffernode->next;
        }
        printf("                    Total savings for \033[33m%s\033[0m: \033[32m%f\033[0m\n",username,totalsave);
        printf("                    -----------------------------------------------------------\n");
    } else {
        printf("                    \033[31mNo Savings found for user:\033[0m %s\n", username);
        printf("                    -----------------------------------------------------------\n");
    }
    struct node *buffernode;
	while(heaD!=NULL){
		buffernode=heaD;
		heaD=heaD->next;
		free(buffernode);
    fclose(f);
}
}
