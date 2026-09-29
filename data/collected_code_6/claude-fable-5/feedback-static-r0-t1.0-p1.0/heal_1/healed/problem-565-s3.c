#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char **split_string(const char *input, size_t *count)
{
    size_t len;
    size_t i;
    char **result;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (len > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(len * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = malloc(2);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = input[i];
        result[i][1] = '\0';
    }

    *count = len;
    return result;
}

void free_split(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int main(void)
{
    const char *text = "Hello, World!";
    size_t count = 0;
    size_t i;
    char **parts;

    parts = split_string(text, &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", parts[i]) < 0) {
            free_split(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);
    return EXIT_SUCCESS;
}