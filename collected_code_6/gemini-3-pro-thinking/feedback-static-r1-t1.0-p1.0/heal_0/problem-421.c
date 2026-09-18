#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_tuple(const char **tuple, size_t num_elements, const char *delimiter);

char *concatenate_tuple(const char **tuple, size_t num_elements, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || num_elements == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_len = strlen(delimiter);

    for (size_t i = 0; i < num_elements; ++i) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strlen(tuple[i]);
    }

    total_length += (num_elements - 1) * delim_len + 1;

    char *result = (char *)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char *current_pos = result;
    for (size_t i = 0; i < num_elements; ++i) {
        size_t len = strlen(tuple[i]);
        memcpy(current_pos, tuple[i], len);
        current_pos += len;

        if (i < num_elements - 1) {
            memcpy(current_pos, delimiter, delim_len);
            current_pos += delim_len;
        }
    }
    *current_pos = '\0';

    return result;
}

int main(void) {
    const char *my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t num_elements = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuple(my_tuple, num_elements, delimiter);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}