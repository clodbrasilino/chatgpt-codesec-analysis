#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *position;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return NULL;
        }
    }

    delimiter_length = strlen(delimiter);
    total_length = 0;

    for (i = 0; i < count; i++) {
        size_t element_length = strlen(elements[i]);
        if (total_length > SIZE_MAX - element_length) {
            return NULL;
        }
        total_length += element_length;
        if (i < count - 1) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    for (i = 0; i < count; i++) {
        size_t element_length = strlen(elements[i]);
        memcpy(position, elements[i], element_length);
        position += element_length;
        if (i < count - 1) {
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }
    *position = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = { "ID", "is", "4", "UTS" };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *joined;

    joined = concatenate_tuple(tuple, count, "-");
    if (joined == NULL) {
        fprintf(stderr, "Failed to concatenate tuple\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}