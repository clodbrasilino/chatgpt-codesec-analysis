#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void searchStrings(char *string, char *pattern) {
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
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char *string = "This is a test string.";
    char *pattern = "test";

    searchStrings(string, pattern);

    return 0;
}