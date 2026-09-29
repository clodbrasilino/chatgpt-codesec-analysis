#include <errno.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int matches_pattern(const char *string, bool *matches)
{
    static const char pattern[] = "^ab*$";
    regex_t regex;
    int result;

    if (string == NULL || matches == NULL) {
        return REG_INVARG;
    }

    *matches = false;

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    if (result == 0) {
        *matches = true;
        result = 0;
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    bool matches;
    int result;

    errno = 0;
    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            perror("getline");
        } else {
            fputs("No input provided\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    result = matches_pattern(input, &matches);
    free(input);

    if (result != 0) {
        size_t message_size = regerror(result, NULL, NULL, 0);
        char *message = malloc(message_size);

        if (message == NULL) {
            fputs("Regex error\n", stderr);
            return EXIT_FAILURE;
        }

        regerror(result, NULL, message, message_size);
        fprintf(stderr, "Regex error: %s\n", message);
        free(message);
        return EXIT_FAILURE;
    }

    puts(matches ? "Match" : "No match");
    return EXIT_SUCCESS;
}