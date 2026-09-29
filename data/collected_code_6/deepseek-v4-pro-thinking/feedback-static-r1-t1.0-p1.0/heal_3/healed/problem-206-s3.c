#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concat_strings(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return NULL;
    }

    int needed = snprintf(NULL, 0, "%s%s", left, right);
    if (needed < 0) {
        return NULL;
    }

    size_t total = (size_t)needed + 1;

    if (total == 0) {
        return NULL;
    }

    char *result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    snprintf(result, total, "%s%s", left, right);
    return result;
}

char **adjacent_concatenate(const char **elements, size_t count, size_t *out_count)
{
    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (elements == NULL || count < 2) {
        return NULL;
    }

    size_t result_count = count - 1;

    if (result_count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc(result_count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t i;
    for (i = 0; i < result_count; i++) {
        result[i] = concat_strings(elements[i], elements[i + 1]);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    *out_count = result_count;
    return result;
}

int main(void)
{
    const char *data[] = {"GFG", "is", "best", "for", "geeks"};
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t out_count = 0;
    char **result = adjacent_concatenate(data, count, &out_count);

    if (result == NULL) {
        return 1;
    }

    size_t i;
    for (i = 0; i < out_count; i++) {
        printf("%s\n", result[i]);
    }

    for (i = 0; i < out_count; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}