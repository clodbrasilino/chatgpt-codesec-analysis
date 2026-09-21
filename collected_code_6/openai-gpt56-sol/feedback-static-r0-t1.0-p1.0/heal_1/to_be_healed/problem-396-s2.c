#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (result == REG_NOMATCH)
        return 0;

    return result;
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

    if (length > 0 && line[length - 1] == '\n')
        line[--length] = '\0';

    if (length > 0 && line[length - 1] == '\r')
        line[--length] = '\0';

    result = starts_and_ends_with_same_character(line, &matches);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];

        regerror(result, NULL, error_message, sizeof(error_message));
        fprintf(stderr, "Regex error: %s\n", error_message);
        free(line);
        return EXIT_FAILURE;
    }

    puts(matches ? "Yes" : "No");
    free(line);
    return EXIT_SUCCESS;
}