#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

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
    char email[257];
    size_t len;
    int c;
    
    printf("Enter email address: ");
    if (fgets(email, sizeof(email), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    email[sizeof(email) - 1] = '\0';
    
    len = strnlen(email, sizeof(email));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    if (email[len - 1] == '\n') {
        email[len - 1] = '\0';
    } else if (len == sizeof(email) - 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (is_valid_email(email)) {
        printf("Valid email address\n");
    } else {
        printf("Invalid email address\n");
    }
    
    return EXIT_SUCCESS;
}