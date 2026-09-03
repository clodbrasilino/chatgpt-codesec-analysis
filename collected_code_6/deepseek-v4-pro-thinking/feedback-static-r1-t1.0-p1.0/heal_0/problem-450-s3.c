#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *input[], size_t count, size_t target_len, size_t *out_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t k;
    size_t len;
    char *copy;

    if (input == NULL || out_count == NULL) {
        return NULL;
    }

    if (count > ((size_t)-1) / sizeof(char *)) {
        return NULL;
    }

    result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }

        len = strlen(input[i]);
        if (len != target_len) {
            continue;
        }

        if (target_len == (size_t)-1) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }

        copy = malloc(target_len + 1);
        if (copy == NULL) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }

        memcpy(copy, input[i], target_len);
        copy[target_len] = '\0';
        result[j++] = copy;
    }

    result[j] = NULL;
    *out_count = j;
    return result;
}

void free_strings(char **strings)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *input[] = {"hello", "world", "C", "code", "test"};
    size_t count = sizeof(input) / sizeof(input[0]);
    size_t out_count = 0;
    size_t i;
    char **result;

    result = extract_strings(input, count, 5, &out_count);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < out_count; i++) {
        printf("%s\n", result[i]);
    }

    free_strings(result);
    return EXIT_SUCCESS;
}