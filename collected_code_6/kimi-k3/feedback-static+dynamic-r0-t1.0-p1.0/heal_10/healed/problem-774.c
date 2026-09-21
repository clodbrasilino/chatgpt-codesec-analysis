#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 254
#define BUFFER_SIZE (MAX_EMAIL_LENGTH + 2)

int is_valid_email(const char *email) {
    regex_t regex;
    int ret;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";
    
    if (email == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return (ret == 0) ? 1 : 0;
}

int main(void) {
    char email[BUFFER_SIZE];
    size_t len;
    bool input_too_long = false;
    
    printf("Enter email address: ");
    if (fgets(email, sizeof(email), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(email, sizeof(email));
    
    if (len == sizeof(email) - 1 && email[len - 1] != '\n') {
        input_too_long = true;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
        len--;
    }
    
    if (input_too_long) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    if (is_valid_email(email)) {
        printf("Valid email address\n");
    } else {
        printf("Invalid email address\n");
    }
    
    return EXIT_SUCCESS;
}