#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <limits.h>

void searchStrings(const char *string, const char *pattern) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    if (!ret) {
        printf("Match found\n");
    } else if (ret == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        char *error_message = malloc(REG_EBRACE + 1); 
        if (error_message) {
            regerror(ret, &regex, error_message, REG_EBRACE + 1);
            fprintf(stderr, "Regex match failed: %s\n", error_message);
            free(error_message);
            exit(1);
        }
    }

    regfree(&regex);
}

int main() {
    const char *string = "This is a test string.";
    const char *pattern = "test";

    searchStrings(string, pattern);

    return 0;
}