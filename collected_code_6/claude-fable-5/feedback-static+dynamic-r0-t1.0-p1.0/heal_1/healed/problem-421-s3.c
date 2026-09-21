#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_tuple(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t element_length;
    size_t offset;
    size_t i;
    char *result;

    if (elements == NULL || delimiter == NULL || count == 0U) {
        return NULL;
    }

    delimiter_length = strlen(delimiter);
    total_length = 0U;

    for (i = 0U; i < count; i++) {
        if (elements[i] == NULL) {
            return NULL;
        }
        element_length = strlen(elements[i]);
        if (total_length > (size_t)-1 - element_length) {
            return NULL;
        }
        total_length += element_length;
    }

    if (delimiter_length != 0U && (count - 1U) > ((size_t)-1 - total_length) / delimiter_length) {
        return NULL;
    }
    total_length += delimiter_length * (count - 1U);

    if (total_length == (size_t)-1) {
        return NULL;
    }

    result = malloc(total_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    offset = 0U;
    for (i = 0U; i < count; i++) {
        if (i > 0U && delimiter_length > 0U) {
            memcpy(result + offset, delimiter, delimiter_length);
            offset += delimiter_length;
        }
        element_length = strlen(elements[i]);
        if (element_length > 0U) {
            memcpy(result + offset, elements[i], element_length);
            offset += element_length;
        }
    }
    result[offset] = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = {"ID", "is", "4", "UTS"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *joined;

    joined = concatenate_tuple(tuple, count, "-");
    if (joined == NULL) {
        fprintf(stderr, "Error: concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}