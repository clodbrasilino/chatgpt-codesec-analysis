#include <stdio.h>
#include <stdlib.h>

char* concatenate_with_delimiter(const char* tuple[], size_t length, const char* delimiter) {
    if (length == 0) return NULL;

    size_t delimiter_length = 0;
    while (delimiter[delimiter_length] != '\0') delimiter_length++;

    size_t total_length = 0;
    for (size_t i = 0; i < length; ++i) {
        size_t str_length = 0;
        while (tuple[i][str_length] != '\0') str_length++;
        total_length += str_length;
    }
    total_length += delimiter_length * (length - 1);

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) return NULL;

    size_t current_length = 0;
    for (size_t i = 0; i < length; ++i) {
        size_t str_length = 0;
        while (tuple[i][str_length] != '\0') {
            result[current_length++] = tuple[i][str_length++];
        }
        if (i < length - 1) {
            for (size_t j = 0; j < delimiter_length; ++j) {
                result[current_length++] = delimiter[j];
            }
        }
    }
    result[current_length] = '\0';

    return result;
}

void free_concatenated_string(char* str) {
    if (str != NULL) {
        free(str);
    }
}

int main() {
    const char* tuple[] = {"Hello", "World", "C", "Programming"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* result = concatenate_with_delimiter(tuple, length, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free_concatenated_string(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}