#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "(^|[^[:alnum:]_])([[:alpha:]]{3,5})([^[:alnum:]_]|$)";
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return EXIT_FAILURE;
    }

    while ((status = regexec(&regex, cursor, 4, &match, 0)) == 0) {
        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         *  subscripted value is not an array, pointer, or vector
         */
        size_t start = (size_t)match[2].rm_so;
        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         *  subscripted value is not an array, pointer, or vector
         */
        size_t length = (size_t)(match[2].rm_eo - match[2].rm_so);

        if (fwrite(cursor + start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         *  subscripted value is not an array, pointer, or vector
         */
        cursor += match[2].rm_eo;
    }

    if (status != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
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