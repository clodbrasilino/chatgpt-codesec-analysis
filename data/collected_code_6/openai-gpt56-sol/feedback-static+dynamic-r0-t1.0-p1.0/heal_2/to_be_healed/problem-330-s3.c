#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{3,5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char message[256];
        regerror(status, &regex, message, sizeof message);
        fprintf(stderr, "regcomp failed: %s\n", message);
        return -1;
    }

    while ((status = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;

        if (start < 0 || end < start) {
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)(end - start), cursor + start) < 0) {
            regfree(&regex);
            return -1;
        }

        if (matches[0].rm_eo <= 0) {
            break;
        }

        cursor += matches[0].rm_eo;
    }

    if (status != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char message[256];
        regerror(status, &regex, message, sizeof message);
        fprintf(stderr, "regexec failed: %s\n", message);
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
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 256 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large\n", stderr);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        perror("getchar");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (find_words(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}