#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0;

    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count = 0;
    size_t i;
    size_t j = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    result = malloc(len + (space_count * 2) + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[j] = '%';
            result[j + 1] = '2';
            result[j + 2] = '0';
            j += 3;
        } else {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    char *converted;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    converted = replace_spaces(input);
    if (converted == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    free(converted);
    converted = NULL;

    return EXIT_SUCCESS;
}