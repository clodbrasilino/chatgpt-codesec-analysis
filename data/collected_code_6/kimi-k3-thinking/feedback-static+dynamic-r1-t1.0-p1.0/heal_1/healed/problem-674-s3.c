#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, MAX_INPUT_LENGTH);

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
    memcpy(copy, str, len);
    copy[len] = '\0';

    char **seen = NULL;
    size_t seen_count = 0;
    size_t out_len = 0;

    for (char *word = strtok(copy, " \t\n"); word != NULL; word = strtok(NULL, " \t\n")) {
        int found = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], word) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            continue;
        }

        char **tmp = realloc(seen, (seen_count + 1) * sizeof(*tmp));
        if (tmp == NULL) {
            free(seen);
            free(copy);
            free(result);
            return NULL;
        }
        seen = tmp;
        seen[seen_count++] = word;

        if (out_len > 0) {
            result[out_len++] = ' ';
            result[out_len] = '\0';
        }

        size_t remaining = (len + 1) - out_len;
        int written = snprintf(result + out_len, remaining, "%s", word);
        if (written < 0 || (size_t)written >= remaining) {
            free(seen);
            free(copy);
            free(result);
            return NULL;
        }
        out_len += (size_t)written;
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    const char *input = "Python Exercises Practice Solution Exercises";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}