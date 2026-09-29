#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024

static char *duplicate_string(const char *src)
{
    size_t len;
    char *dup;

    if (src == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    dup = malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dup, src, len + 1);
    return dup;
}

char *find_first_repeated_word(const char *input)
{
    char *copy;
    char *token;
    char *result;
    const char *delims = " \t\r\n.,;:!?\"'()";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *seen[MAX_WORDS];
    size_t count;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    copy = duplicate_string(input);
    if (copy == NULL) {
        return NULL;
    }

    result = NULL;
    count = 0;

    token = strtok(copy, delims);
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
        token = strtok(NULL, delims);
    }

cleanup:
    for (i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(copy);
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog";
    char *repeated;

    repeated = find_first_repeated_word(text);
    if (repeated != NULL) {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
        free(repeated);
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}