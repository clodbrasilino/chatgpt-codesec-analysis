#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SAFE_STRING_MAX 65536U

char *concat_strings(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return NULL;
    }

    size_t left_len = strnlen(left, SAFE_STRING_MAX);
    if (left_len == SAFE_STRING_MAX) {
        return NULL;
    }
    size_t right_len = strnlen(right, SAFE_STRING_MAX);
    if (right_len == SAFE_STRING_MAX) {
        return NULL;
    }

    if (left_len > SIZE_MAX - right_len) {
        return NULL;
    }
    size_t total_len = left_len + right_len;

    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, left, left_len);
    memcpy(result + left_len, right, right_len);
    result[total_len] = '\0';

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