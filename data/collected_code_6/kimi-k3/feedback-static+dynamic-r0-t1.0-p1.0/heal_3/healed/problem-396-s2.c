#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

int starts_ends_same_char(const char *str) {
    regex_t regex;
    int reti;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    reti = regcomp(&regex, "^(.).*\\1$|^.$", REG_EXTENDED);
    if (reti != 0) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t line_length;
    char *newline;

    errno = 0;
    line_length = getline(&input, &input_size, stdin);
    
    if (line_length == -1) {
        if (errno == ENOMEM) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        free(input);
        return 1;
    }

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    if (starts_ends_same_char(input)) {
        printf("String starts and ends with the same character.\n");
    } else {
        printf("String does not start and end with the same character.\n");
    }

    free(input);
    return 0;
}