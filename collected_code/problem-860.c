#include <stdio.h>
#include <regex.h>

// Function to check if a string ends with only alphanumeric characters using regex
int endsWithAlphanumeric(char *string) {
    regex_t regex;
    int reti;

    // Compile the regex pattern
    reti = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1;
    }

    // Execute the regex on the string
    reti = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;  // String ends with only alphanumeric characters
    } else if (reti == REG_NOMATCH) {
        return 0;  // String does not end with only alphanumeric characters
    } else {
        fprintf(stderr, "Regex match failed\n");
        return -1;
    }
}