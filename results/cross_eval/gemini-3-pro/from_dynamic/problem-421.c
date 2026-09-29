#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] != NULL) {
            total_length += strlen(tuple[i]);
        }
        if (i < size - 1) {
            total_length += delim_length;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] != NULL) {
            strncat(result, tuple[i], total_length - strlen(result));
        }
        if (i < size - 1) {
            strncat(result, delimiter, total_length - strlen(result));
        }
    }

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);

    if (result != NULL) {
        printf("Concatenated string: %s\n", result);
        free(result);
        result = NULL;
    } else {
        printf("Failed to concatenate the tuple.\n");
    }

    return 0;
}