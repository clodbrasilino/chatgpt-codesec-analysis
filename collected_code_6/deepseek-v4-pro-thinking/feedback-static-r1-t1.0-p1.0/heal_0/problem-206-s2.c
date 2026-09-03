#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adjacent_concatenate(char **strings, int count, char ***result, int *result_count)
{
    if (strings == NULL || result == NULL || result_count == NULL || count < 0) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count < 2) {
        return 0;
    }

    int out_count = count - 1;
    char **out = malloc((size_t)out_count * sizeof(char *));
    if (out == NULL) {
        return -1;
    }

    for (int i = 0; i < out_count; i++) {
        out[i] = NULL;
    }

    for (int i = 0; i < out_count; i++) {
        if (strings[i] == NULL || strings[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(out[j]);
            }
            free(out);
            return -1;
        }

        size_t len1 = strlen(strings[i]);
        size_t len2 = strlen(strings[i + 1]);
        size_t total = len1 + len2 + 1;

        if (total <= len1 || total <= len2) {
            for (int j = 0; j < i; j++) {
                free(out[j]);
            }
            free(out);
            return -1;
        }

        char *combined = malloc(total);
        if (combined == NULL) {
            for (int j = 0; j < i; j++) {
                free(out[j]);
            }
            free(out);
            return -1;
        }

        memcpy(combined, strings[i], len1);
        memcpy(combined + len1, strings[i + 1], len2 + 1);
        out[i] = combined;
    }

    *result = out;
    *result_count = out_count;
    return 0;
}

int main(void)
{
    char *tuple[] = { "Geeks", "for", "Geeks", "Best" };
    int count = (int)(sizeof(tuple) / sizeof(tuple[0]));
    char **result = NULL;
    int result_count = 0;

    if (adjacent_concatenate(tuple, count, &result, &result_count) != 0) {
        fprintf(stderr, "Error during concatenation\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    for (int i = 0; i < result_count; i++) {
        free(result[i]);
    }
    free(result);

    return EXIT_SUCCESS;
}