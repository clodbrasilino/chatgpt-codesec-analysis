#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_length = strlen(delimiter);

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] != NULL) {
            total_length += strlen(tuple[i]);
        }
    }

    total_length += delim_length * (size - 1);

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] != NULL) {
            strcat(result, tuple[i]);
        }
        if (i < size - 1) {
            strcat(result, delimiter);
        }
    }

    return result;
}

int main(void) {
    const char* tuple[] = {"Hello", "world", "this", "is", "C"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* concatenated = concatenate_tuple(tuple, size, delimiter);

    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}