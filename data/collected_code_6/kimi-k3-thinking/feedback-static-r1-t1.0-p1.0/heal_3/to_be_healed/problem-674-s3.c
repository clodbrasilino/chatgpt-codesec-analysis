#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 65536

static int safe_memcpy(void *dst, size_t dst_capacity, const void *src, size_t count)
{
    if (dst == NULL || src == NULL || count > dst_capacity) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, count);
    return 0;
}

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return NULL;
    }

    size_t result_capacity = len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    size_t copy_capacity = len + 1;
    char *copy = malloc(copy_capacity);
    if (copy == NULL) {
        free(result);
        return NULL;
    }

    if (safe_memcpy(copy, copy_capacity, str, len + 1) != 0) {
        free(copy);
        free(result);
        return NULL;
    }

    char **seen = NULL;
    size_t seen_count = 0;
    size_t out_len = 0;

    char *word = strtok(copy, " \t\n");
    while (word != NULL) {
        int found = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], word) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            char **tmp = realloc(seen, (seen_count + 1) * sizeof(*seen));
            if (tmp == NULL) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }
            seen = tmp;
            seen[seen_count] = word;
            seen_count++;

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t wlen = strlen(word);
            size_t sep = (out_len > 0) ? 1 : 0;
            size_t needed = sep + wlen + 1;

            if (out_len >= result_capacity || needed > result_capacity - out_len) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }

            if (sep) {
                result[out_len++] = ' ';
            }

            if (safe_memcpy(result + out_len, result_capacity - out_len, word, wlen) != 0) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }
            out_len += wlen;
            result[out_len] = '\0';
        }

        word = strtok(NULL, " \t\n");
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    const char *input = "the quick brown fox jumps over the lazy dog the fox";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}