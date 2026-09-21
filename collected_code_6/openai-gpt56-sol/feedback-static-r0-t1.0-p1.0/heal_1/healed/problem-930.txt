#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static int matches_pattern(const char *string)
{
    static const char pattern[] = "^ab*$";
    regex_t regex;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    if (result == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);

        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    result = matches_pattern(input);
    free(input);

    if (result < 0) {
        fprintf(stderr, "Regex operation failed.\n");
        return EXIT_FAILURE;
    }

    puts(result ? "Match" : "No match");
    return EXIT_SUCCESS;
}