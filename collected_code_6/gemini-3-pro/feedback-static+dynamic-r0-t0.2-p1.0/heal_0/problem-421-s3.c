#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (!tuple || !delimiter || tuple_size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i]) {
            total_length += strlen(tuple[i]);
        }
    }

    total_length += delimiter_length * (tuple_size - 1) + 1;

    char* result = (char*)malloc(total_length);
    if (!result) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i]) {
            strcat(result, tuple[i]);
        }
        if (i < tuple_size - 1) {
            strcat(result, delimiter);
        }
    }

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated_string = concatenate_tuple(tuple, tuple_size, delimiter);

    if (concatenated_string) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}