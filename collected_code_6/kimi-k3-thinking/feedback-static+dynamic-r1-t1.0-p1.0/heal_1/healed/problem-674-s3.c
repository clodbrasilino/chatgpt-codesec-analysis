#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
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
    strcpy(copy, str);

    char **seen = NULL;
    size_t seen_count = 0;
    size_t out_len = 0;

    char *word = strtok(copy, " \t\n\r");
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
            seen[seen_count++] = word;

            size_t wlen = strlen(word);
            if (out_len > 0) {
                result[out_len++] = ' ';
            }
            memcpy(result + out_len, word, wlen);
            out_len += wlen;
            result[out_len] = '\0';
        }

        word = strtok(NULL, " \t\n\r");
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read the input string\n");
        return EXIT_FAILURE;
    }

    char *output = remove_duplicate_words(input);
    if (output == NULL) {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}