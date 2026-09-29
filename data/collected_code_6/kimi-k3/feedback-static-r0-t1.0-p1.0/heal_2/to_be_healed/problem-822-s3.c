#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 128

bool isValidPassword(const char *password) {
    if (password == NULL) {
        return false;
    }
    
    size_t length = 0;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    while (length <= MAX_LENGTH && password[length] != '\0') {
        unsigned char c = (unsigned char)password[length];
        
        if (isspace(c)) {
            return false;
        }
        
        if (isupper(c)) {
            hasUpper = true;
        } else if (islower(c)) {
            hasLower = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (ispunct(c)) {
            hasSpecial = true;
        }
        
        length++;
    }
    
    if (length < MIN_LENGTH || length > MAX_LENGTH) {
        return false;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[MAX_LENGTH + 2];
    
    printf("Enter password: ");
    
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strcspn(password, "\n");
    
    if (password[len] == '\n') {
        password[len] = '\0';
    } else if (len == sizeof(password) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Password too long\n");
        return EXIT_FAILURE;
    }
    
    if (isValidPassword(password)) {
        printf("Password is valid\n");
        return EXIT_SUCCESS;
    } else {
        printf("Password is invalid\n");
        return EXIT_FAILURE;
    }
}