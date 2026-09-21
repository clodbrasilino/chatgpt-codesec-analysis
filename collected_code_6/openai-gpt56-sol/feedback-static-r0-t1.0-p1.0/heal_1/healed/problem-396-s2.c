#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int starts_and_ends_with_same_character(const char *string, int *matches)
{
    static const char pattern[] = "^(.)(.*\\1)?$";
    regex_t regex;
    int result;

    if (string == NULL || matches == NULL)
        return REG_BADPAT;

    *matches = 0;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0)
        return result;

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *matches = 1;
        return 0;
    }

    return result == REG_NOMATCH ? 0 : result;
}

static void print_regex_error(int result)
{
    size_t size = regerror(result, NULL, NULL, 0);
    char *message;

    if (size == 0) {
        fputs("Regex error\n", stderr);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fputs("Regex error\n", stderr);
        return;
    }

    regerror(result, NULL, message, size);
    fprintf(stderr, "Regex error: %s\n", message);
    free(message);
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    int matches;
    int result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    result = starts_and_ends_with_same_character(line, &matches);
    if (result != 0) {
        print_regex_error(result);
        free(line);
        return EXIT_FAILURE;
    }

    puts(matches ? "Yes" : "No");
    free(line);
    return EXIT_SUCCESS;
}