#include <regex.h>

int isValidEmail(const char *email) {
    // Regular expression pattern for email validation
    const char *pattern = "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$";

    // Compile the regular expression
    regex_t regex;
    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        return 0; // Failed to compile regex
    }

    // Execute the regular expression
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1; // Email is valid
    } else if (reti == REG_NOMATCH) {
        return 0; // Email is invalid
    } else {
        return 0; // Error occurred while executing regex
    }
}