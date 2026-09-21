#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define INPUT_SIZE 1024

static void print_regex_error(int ret, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(ret, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf != NULL) {
        regerror(ret, regex, errbuf, needed);
        fprintf(stderr, "%s: %s\n", context, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unknown error (allocation failed)\n", context);
    }
}

int count_matches(const char *pattern, const char *str, int *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (pattern == NULL || str == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    cursor = str;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "Regex execution failed");
            regfree(&regex);
            return -1;
        }
        (*count)++;
        if (match.rm_eo <= match.rm_so) {
            cursor += 1;
        } else {
            cursor += match.rm_eo;
        }
    }

    regfree(&regex);
    return 0;
}

int classify_string(const char *str, int *upper, int *lower,
                    int *digit, int *special)
{
    if (str == NULL || upper == NULL || lower == NULL ||
        digit == NULL || special == NULL) {
        return -1;
    }

    if (count_matches("[A-Z]", str, upper) != 0) {
        return -1;
    }
    if (count_matches("[a-z]", str, lower) != 0) {
        return -1;
    }
    if (count_matches("[0-9]", str, digit) != 0) {
        return -1;
    }
    if (count_matches("[^A-Za-z0-9]", str, special) != 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    memset(input, 0, sizeof(input));

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';
    input[strcspn(input, "\n")] = '\0';

    if (classify_string(input, &upper, &lower, &digit, &special) != 0) {
        fprintf(stderr, "Classification failed\n");
        return EXIT_FAILURE;
    }

    printf("Uppercase letters: %d\n", upper);
    printf("Lowercase letters: %d\n", lower);
    printf("Numeric digits:    %d\n", digit);
    printf("Special characters: %d\n", special);

    return EXIT_SUCCESS;
}