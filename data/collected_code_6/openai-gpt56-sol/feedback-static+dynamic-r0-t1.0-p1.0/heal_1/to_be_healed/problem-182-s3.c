#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
    int status;

    if (input == NULL || pattern == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        ++(*count);
        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

static int count_character_types(const char *input, CharacterCounts *counts)
{
    size_t accounted;

    if (input == NULL || counts == NULL) {
        return -1;
    }

    memset(counts, 0, sizeof(*counts));

    if (count_matches(input, "[A-Z]", &counts->uppercase) != 0 ||
        count_matches(input, "[a-z]", &counts->lowercase) != 0 ||
        count_matches(input, "[0-9]", &counts->numeric) != 0 ||
        count_matches(input, "[^A-Za-z0-9]", &counts->special) != 0) {
        return -1;
    }

    accounted = counts->uppercase + counts->lowercase +
                counts->numeric + counts->special;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return accounted == strlen(input) ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    CharacterCounts counts;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (count_character_types(input, &counts) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %zu\n", counts.uppercase);
    printf("Lowercase: %zu\n", counts.lowercase);
    printf("Numeric: %zu\n", counts.numeric);
    printf("Special: %zu\n", counts.special);

    free(input);
    return EXIT_SUCCESS;
}