#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *input)
{
    size_t len;
    char *copy;
    char *result;
    char **seen;
    size_t seen_count;
    size_t seen_cap;
    char *token;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);

    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, input, len + 1U);

    result = malloc(len + 1U);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    result[0] = '\0';

    seen = NULL;
    seen_count = 0U;
    seen_cap = 0U;

    token = strtok(copy, " \t\n");
    while (token != NULL) {
        int is_duplicate = 0;
        size_t i;

        for (i = 0U; i < seen_count; i++) {
            if (strcmp(seen[i], token) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate == 0) {
            if (seen_count == seen_cap) {
                size_t new_cap = (seen_cap == 0U) ? 8U : (seen_cap * 2U);
                char **tmp = realloc(seen, new_cap * sizeof(char *));
                if (tmp == NULL) {
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                seen = tmp;
                seen_cap = new_cap;
            }
            seen[seen_count] = token;
            seen_count++;

            if (result[0] != '\0') {
                strcat(result, " ");
            }
            strcat(result, token);
        }

        token = strtok(NULL, " \t\n");
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog the quick fox";
    char *deduplicated;

    deduplicated = remove_duplicate_words(text);
    if (deduplicated == NULL) {
        fprintf(stderr, "Error: failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", text);
    printf("Result:   %s\n", deduplicated);

    free(deduplicated);
    return EXIT_SUCCESS;
}