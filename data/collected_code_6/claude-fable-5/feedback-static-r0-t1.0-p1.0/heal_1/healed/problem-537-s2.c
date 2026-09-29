#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_INPUT_LEN 4096

static char *duplicate_string(const char *src, size_t max_len)
{
    size_t len;
    char *dup;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, max_len);
    if (len >= max_len) {
        return NULL;
    }

    dup = malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    memcpy(dup, src, len);
    dup[len] = '\0';
    return dup;
}

char *find_first_repeated_word(const char *input)
{
    char *copy;
    char *token;
    char *saveptr;
    char *result;
    const char *delims = " \t\r\n.,;:!?\"'()";
    char **seen;
    size_t count;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    copy = duplicate_string(input, MAX_INPUT_LEN);
    if (copy == NULL) {
        return NULL;
    }

    seen = calloc(MAX_WORDS, sizeof(char *));
    if (seen == NULL) {
        free(copy);
        return NULL;
    }

    result = NULL;
    count = 0;
    saveptr = NULL;

    token = strtok_r(copy, delims, &saveptr);
    while (token != NULL && count < MAX_WORDS) {
        for (i = 0; i < count; i++) {
            if (strcmp(seen[i], token) == 0) {
                result = duplicate_string(token, MAX_INPUT_LEN);
                goto cleanup;
            }
        }
        seen[count] = duplicate_string(token, MAX_INPUT_LEN);
        if (seen[count] == NULL) {
            goto cleanup;
        }
        count++;
        token = strtok_r(NULL, delims, &saveptr);
    }

cleanup:
    for (i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(seen);
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