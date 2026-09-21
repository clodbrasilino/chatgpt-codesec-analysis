#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t uppercase;
    size_t lowercase;
    size_t numeric;
    size_t special;
} CharacterCounts;

static int count_matches(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor = input;
    int result;

    *count = 0;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];
        regerror(result, NULL, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return -1;
    }

    for (;;) {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char error_message[256];
            regerror(result, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex matching failed: %s\n", error_message);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match range\n");
            regfree(&regex);
            return -1;
        }

        ++(*count);
        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

static int classify_characters(const char *input, CharacterCounts *counts)
{
    if (input == NULL || counts == NULL) {
        return -1;
    }

    if (count_matches(input, "[A-Z]", &counts->uppercase) != 0 ||
        count_matches(input, "[a-z]", &counts->lowercase) != 0 ||
        count_matches(input, "[0-9]", &counts->numeric) != 0 ||
        count_matches(input, "[^A-Za-z0-9]", &counts->special) != 0) {
        return -1;
    }

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

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
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