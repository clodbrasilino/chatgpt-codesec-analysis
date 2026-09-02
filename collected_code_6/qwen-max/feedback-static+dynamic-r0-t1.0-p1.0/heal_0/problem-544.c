#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuples(const char *tuple[], size_t length, size_t tuple_size) {
    size_t total_len = 0;
    for (size_t i = 0; i < length; ++i) {
        total_len += strlen(tuple[i]) + 1; // +1 for comma or closing parenthesis
    }
    total_len += length - 1; // for commas
    total_len += 2; // for opening and closing parentheses

    char *result = (char *)malloc(total_len + 1); // +1 for null terminator
    if (result == NULL) {
        return NULL; // handle memory allocation failure
    }

    size_t index = 0;
    result[index++] = '(';
    for (size_t i = 0; i < length; ++i) {
        strcpy(&result[index], tuple[i]);
        index += strlen(tuple[i]);
        if (i < length - 1) {
            result[index++] = ',';
        } else {
            result[index++] = ')';
        }
    }
    result[index] = '\0'; // null-terminate the string
    return result;
}

int main() {
    const char *tuples[] = {"1", "2", "3"};
    size_t length = 3;
    size_t tuple_size = 1;

    char *flattened = flatten_tuples(tuples, length, tuple_size);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}