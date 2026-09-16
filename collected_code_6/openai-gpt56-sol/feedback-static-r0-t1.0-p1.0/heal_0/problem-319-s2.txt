#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int find_five_letter_words(const char *text)
{
    const char *pattern = "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor;
    int status;

    if (text == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "regcomp failed: %s\n", error_message);
        return -1;
    }

    cursor = text;

    while ((status = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        size_t word_length;

        if (matches[2].rm_so < 0 || matches[2].rm_eo < matches[2].rm_so) {
            regfree(&regex);
            return -1;
        }

        word_length = (size_t)(matches[2].rm_eo - matches[2].rm_so);

        if (printf("%.*s\n",
                   (int)word_length,
                   cursor + matches[2].rm_so) < 0) {
            regfree(&regex);
            return -1;
        }

        if (matches[2].rm_eo == 0) {
            regfree(&regex);
            return -1;
        }

        cursor += matches[2].rm_eo;
    }

    if (status != REG_NOMATCH) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "regexec failed: %s\n", error_message);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    if (find_five_letter_words(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}