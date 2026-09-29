#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} string_tuple_t;

void free_tuple(string_tuple_t *tuple) {
    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
}

string_tuple_t *convert_to_tuple(const char *input) {
    if (input == NULL) return NULL;

    size_t length = strlen(input);
    if (length == 0) return NULL;

    size_t count = 1;
    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ',') {
            count++;
        }
    }

    string_tuple_t *tuple = (string_tuple_t *)malloc(sizeof(string_tuple_t));
    if (tuple == NULL) return NULL;

    tuple->elements = (char **)malloc(count * sizeof(char *));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->count = count;
    size_t start = 0;
    size_t index = 0;
    for (size_t i = 0; i <= length; ++i) {
        if (input[i] == ',' || input[i] == '\0') {
            tuple->elements[index] = (char *)malloc(i - start + 1);
            if (tuple->elements[index] == NULL) {
                free_tuple(tuple);
                return NULL;
            }
            strncpy(tuple->elements[index], &input[start], i - start);
            tuple->elements[index][i - start] = '\0';
            start = i + 1;
            index++;
        }
    }

    return tuple;
}

int main() {
    const char *input = "apple,banana,orange";
    string_tuple_t *tuple = convert_to_tuple(input);

    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; ++i) {
            printf("%s\n", tuple->elements[i]);
        }
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to convert string to tuple.\n");
    }

    return 0;
}