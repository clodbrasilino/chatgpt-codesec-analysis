#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 254

bool is_valid_email(const char *email) {
    regex_t regex;
    int ret;
    bool is_valid = false;
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    
    if (email == NULL || strlen(email) > MAX_EMAIL_LENGTH) {
        return false;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return false;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    if (ret == 0) {
        is_valid = true;
    }
    
    regfree(&regex);
    return is_valid;
}

int main(void) {
    const char *test_emails[] = {
        "user@example.com",
        "user.name@domain.co.uk",
        "user+tag@example.org",
        "invalid@",
        "@invalid.com",
        "invalid@domain",
        "invalid email@domain.com",
        "valid.email@sub.domain.com",
        NULL
    };
    
    for (int i = 0; test_emails[i] != NULL; i++) {
        if (is_valid_email(test_emails[i])) {
            printf("Valid: %s\n", test_emails[i]);
        } else {
            printf("Invalid: %s\n", test_emails[i]);
        }
    }
    
    return 0;
}