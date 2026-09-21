#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 65536

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        free(result);
        return NULL;
    }
    memcpy(copy, str, len + 1);

    char **seen = NULL;
    size_t seen_count = 0;
    size_t out_len = 0;

    char *word = strtok(copy, " \t\n");
    while (word != NULL) {
        int found = 0;
        size_t i;
        for (i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], word) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            char **tmp = realloc(seen, (seen_count + 1) * sizeof(*seen));
            size_t wlen;
            size_t sep;

            if (tmp == NULL) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }
            seen = tmp;
            seen[seen_count] = word;
            seen_count++;

            wlen = strnlen(word, len + 1);
            sep = (out_len > 0) ? 1 : 0;

            if (sep > len - out_len || wlen > len - out_len - sep) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }

            if (sep) {
                result[out_len++] = ' ';
            }
            memcpy(result + out_len, word, wlen);
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