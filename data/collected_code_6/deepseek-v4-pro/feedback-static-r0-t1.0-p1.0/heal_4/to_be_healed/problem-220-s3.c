#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void replace_chars(char *str, int n) {
    int count = 0;
    while (*str && count < n) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            count++;
        }
        str++;
    }
}

int main(void) {
    char *text = NULL;
    size_t bufsize = 0;
    int max_replace;
    long val;
    char *endptr;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    printf("Enter a string: ");
    if (getline(&text, &bufsize, stdin) == -1) {
        free(text);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (text != NULL && strlen(text) > 0) {
        text[strcspn(text, "\n")] = '\0';
    }

    printf("Enter maximum replacements: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        free(text);
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    errno = 0;
    val = strtol(input, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        free(text);
        return 1;
    }
    if (endptr == input || *endptr != '\0') {
        free(text);
        return 1;
    }
    max_replace = (int)val;

    if (max_replace < 0) {
        max_replace = 0;
    }

    replace_chars(text, max_replace);
    printf("Result: %s\n", text);

    free(text);
    return 0;
}