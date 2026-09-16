#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int starts_and_ends_with_same_character(const char *string, int *matches)
{
    regex_t regex;
    const char *pattern = "^(.)(.*\\1)?$";
    int status;

    if (string == NULL || matches == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *matches = 1;
        return 0;
    }

    if (status == REG_NOMATCH) {
        *matches = 0;
        return 0;
    }

    return -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int matches;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (starts_and_ends_with_same_character(input, &matches) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(matches ? "Yes" : "No");
    free(input);

    return EXIT_SUCCESS;
}