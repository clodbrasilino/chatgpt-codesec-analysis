#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 256
#define INPUT_SIZE 1024

static int count_matches(const char *pattern, const char *str, int *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];

    if (pattern == NULL || str == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = str;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            errbuf[sizeof(errbuf) - 1] = '\0';
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
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

static int classify_string(const char *str, int *upper, int *lower,
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
    char *input;
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    input = calloc(INPUT_SIZE, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[INPUT_SIZE - 1] = '\0';
    input[strcspn(input, "\n")] = '\0';

    if (classify_string(input, &upper, &lower, &digit, &special) != 0) {
        fprintf(stderr, "Classification failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Uppercase letters: %d\n", upper);
    printf("Lowercase letters: %d\n", lower);
    printf("Numeric digits:    %d\n", digit);
    printf("Special characters: %d\n", special);

    free(input);
    return EXIT_SUCCESS;
}