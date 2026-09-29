#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char **split_string(const char *str, size_t *count)
{
    char **result = NULL;
    size_t len;
    size_t i;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    *count = len;

    if (len == 0) {
        return NULL;
    }

    result = malloc(len * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }

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
    const char *input = "Hello, World!";
    char **parts;
    size_t count = 0;
    size_t i;

    parts = split_string(input, &count);
    if (parts == NULL) {
        if (count == 0) {
            printf("Input string is empty.\n");
            return EXIT_SUCCESS;
        }
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("Character %zu: %s\n", i, parts[i]);
    }

    free_split(parts, count);

    return EXIT_SUCCESS;
}