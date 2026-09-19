#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* convert_tuple_string_to_int(const char *input, int *output_size) {
    if (input == NULL || output_size == NULL) {
        return NULL;
    }

    int capacity = 10;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        *output_size = 0;
        return NULL;
    }

    char *str_copy = strdup(input);
    char *token = strtok(str_copy, ", ");
    int index = 0;
    while (token != NULL && index < capacity) {
        result[index++] = atoi(token);
        token = strtok(NULL, ", ");
        if (index == capacity) {
            capacity *= 2;
            int *new_result = (int *)realloc(result, capacity * sizeof(int));
            if (new_result == NULL) {
                free(result);
                free(str_copy);
                *output_size = 0;
                return NULL;
            }
            result = new_result;
        }
    }

    *output_size = index;
    result = (int *)realloc(result, index * sizeof(int));
    free(str_copy);
    return result;
}

int main() {
    const char *tuple_string = "(1, 2, 3, 4, 5)";
    int size;
    int *result = convert_tuple_string_to_int(tuple_string + 1, &size);
    if (result != NULL) {
        for (int i = 0; i < size; ++i) {
            printf("%d", result[i]);
            if (i < size - 1) {
                printf(", ");
            }
        }
        free(result);
    } else {
        printf("Conversion failed\n");
    }
    return 0;
}