#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern =
        "(^|[^[:alnum:]_])([[:alpha:]]{3,5})([^[:alnum:]_]|$)";
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return EXIT_FAILURE;
    }

    while ((status = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;
        size_t length;

        if (start < 0 || end < start) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        length = (size_t)(end - start);

        if (fwrite(cursor + (size_t)start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        cursor += (size_t)end;
    }

    if (status != REG_NOMATCH) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "Regex matching failed: %s\n", error_message);
        regfree(&regex);
        return EXIT_FAILURE;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }

        free(input);
        return EXIT_FAILURE;
    }

    result = find_words(input);
    free(input);
    return result;
}