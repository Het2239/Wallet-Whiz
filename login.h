#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>

// Structure definition
struct user_data {
    char username[50];
    char password[50];
};

// Function prototypes
void registerUser(struct user_data *user);
void loginUser(struct user_data *user);

#endif // LOGIN_H
