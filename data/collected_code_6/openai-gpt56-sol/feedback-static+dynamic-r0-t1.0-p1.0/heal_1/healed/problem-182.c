#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
    size_t uppercase;
    size_t lowercase;
    size_t numeric;
    size_t special;
} CharacterCounts;

static void report_regex_error(int error_code, const regex_t *regex,
                               const char *message)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        fprintf(stderr, "%s: error code %d\n", message, error_code);
        return;
    }

    regerror(error_code, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int count_matches(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int result;

    if (input == NULL || pattern == NULL || count == NULL) {
        return -1;
    }

    *count = 0;
    cursor = input;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, NULL, "Regex compilation failed");
        return -1;
    }

    for (;;) {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex, "Regex matching failed");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match range\n");
            regfree(&regex);
            return -1;
        }

        ++(*count);
        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

static int classify_characters(const char *input, CharacterCounts *counts)
{
    CharacterCounts result = {0, 0, 0, 0};

    if (input == NULL || counts == NULL) {
        return -1;
    }

    if (count_matches(input, "[A-Z]", &result.uppercase) != 0 ||
        count_matches(input, "[a-z]", &result.lowercase) != 0 ||
        count_matches(input, "[0-9]", &result.numeric) != 0 ||
        count_matches(input, "[^A-Za-z0-9]", &result.special) != 0) {
        return -1;
    }

    *counts = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    CharacterCounts counts;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[(size_t)length - 1] == '\n') {
        input[(size_t)length - 1] = '\0';
        --length;
    }

    if (length > 0 && input[(size_t)length - 1] == '\r') {
        input[(size_t)length - 1] = '\0';
    }

    if (classify_characters(input, &counts) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %zu\n", counts.uppercase);
    printf("Lowercase: %zu\n", counts.lowercase);
    printf("Numeric: %zu\n", counts.numeric);
    printf("Special: %zu\n", counts.special);

    free(input);
    return EXIT_SUCCESS;
}