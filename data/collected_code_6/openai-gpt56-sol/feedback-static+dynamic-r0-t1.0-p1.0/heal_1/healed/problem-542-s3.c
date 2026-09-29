#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int replace_with_colon(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *cursor;
    int result;

    if (string == NULL) {
        return REG_BADPAT;
    }

    result = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    cursor = string;

    while (*cursor != '\0') {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            result = 0;
            break;
        }

        if (result != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            result = REG_BADPAT;
            break;
        }

        cursor += (size_t)match.rm_so;
        *cursor++ = ':';
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);

        if (ferror(stdin)) {
            perror("getline");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    while (length > 0 &&
           (string[length - 1] == '\n' || string[length - 1] == '\r')) {
        string[--length] = '\0';
    }

    result = replace_with_colon(string);
    if (result != 0) {
        size_t message_size = regerror(result, NULL, NULL, 0);
        char *message = malloc(message_size);

        if (message == NULL) {
            fputs("Unable to allocate regex error message\n", stderr);
            free(string);
            return EXIT_FAILURE;
        }

        regerror(result, NULL, message, message_size);
        fprintf(stderr, "Regex error: %s\n", message);

        free(message);
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        perror("puts");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}