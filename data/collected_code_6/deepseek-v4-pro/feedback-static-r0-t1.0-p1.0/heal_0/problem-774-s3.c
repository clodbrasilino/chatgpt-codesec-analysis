#include <stdio.h>
#include <regex.h>
#include <string.h>

int is_valid_email(const char *email) {
    regex_t regex;
    int ret;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    const char *test_emails[] = {
        "user@example.com",
        "invalid-email",
        "test@domain.co.uk",
        "user@.com",
        "user@domain.",
        NULL
    };
    
    for (int i = 0; test_emails[i] != NULL; i++) {
        printf("%s: %s\n", test_emails[i], 
               is_valid_email(test_emails[i]) ? "Valid" : "Invalid");
    }
    
    return 0;
}