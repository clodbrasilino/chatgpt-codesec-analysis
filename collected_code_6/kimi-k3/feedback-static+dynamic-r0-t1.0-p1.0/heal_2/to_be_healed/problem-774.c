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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char email[256];
    size_t len;
    
    printf("Enter email address: ");
    if (fgets(email, sizeof(email), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(email, sizeof(email));
    if (len == sizeof(email)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }
    
    if (is_valid_email(email)) {
        printf("Valid email address\n");
    } else {
        printf("Invalid email address\n");
    }
    
    return EXIT_SUCCESS;
}