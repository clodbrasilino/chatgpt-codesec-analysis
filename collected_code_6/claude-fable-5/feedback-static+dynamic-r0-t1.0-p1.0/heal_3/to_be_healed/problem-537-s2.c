#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_INPUT_LEN 65536

static char *duplicate_string(const char *src)
{
    size_t len;
    char *dup;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    dup = malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dup, src, len);
    dup[len] = '\0';
    return dup;
}

char *find_first_repeated_word(const char *input)
{
    char *copy;
    char *token;
    char *result;
    char *saveptr;
    const char *delims = " \t\r\n.,;:!?\"'()";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *seen[MAX_WORDS];
    size_t count;
    size_t i;

    if (input == NULL) {
        return duplicate_string("None");
    }

    copy = duplicate_string(input);
    if (copy == NULL) {
        return NULL;
    }

    result = NULL;
    count = 0;
    saveptr = NULL;

    token = strtok_r(copy, delims, &saveptr);
    while (token != NULL && count < MAX_WORDS) {
        for (i = 0; i < count; i++) {
            if (strcmp(seen[i], token) == 0) {
                result = duplicate_string(token);
                goto cleanup;
            }
        }
        seen[count] = duplicate_string(token);
        if (seen[count] == NULL) {
            goto cleanup;
        }
        count++;
        token = strtok_r(NULL, delims, &saveptr);
    }

    result = duplicate_string("None");

cleanup:
    for (i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(copy);
    return result;
}

int main(void)
{
    char *input;
    char *repeated;

    input = malloc(MAX_INPUT_LEN);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    repeated = find_first_repeated_word(input);
    free(input);

    if (repeated == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", repeated) < 0) {
        free(repeated);
        return EXIT_FAILURE;
    }

    free(repeated);
    return EXIT_SUCCESS;
}