#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals_regex(const char *string, const char *pattern) {
    regex_t regex;
    int reti;
    int result = 0;

    if (string == NULL || pattern == NULL) {
        return -1;
    }

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    } else if (reti != REG_NOMATCH) {
        result = -1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {"quick", "fox", "cat", "dog"};
    size_t num_literals = sizeof(literals) / sizeof(literals[0]);
    size_t i;

    for (i = 0; i < num_literals; i++) {
        int found = search_literals_regex(text, literals[i]);
        if (found == 1) {
            printf("Found: %s\n", literals[i]);
        } else if (found == 0) {
            printf("Not found: %s\n", literals[i]);
        } else {
            fprintf(stderr, "Error searching for: %s\n", literals[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}