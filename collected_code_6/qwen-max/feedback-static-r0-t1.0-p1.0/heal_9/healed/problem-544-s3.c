#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char*** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][j] != NULL; ++j) {
            const char* str = tuple_list[i][j];
            size_t len = strlen(str);
            total_length += len + 1;
        }
    }
    if (total_length > 0) --total_length;

    char* result = (char*) malloc(total_length + 1);
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][j] != NULL; ++j) {
            const char* str = tuple_list[i][j];
            size_t len = strlen(str);
            if (index + len > total_length) {
                free(result);
                return NULL;
            }
            memcpy(result + index, str, len);
            index += len;
            if (tuple_list[i][j + 1] != NULL || (i + 1 < tuple_count && tuple_list[i + 1][0] != NULL)) {
                if (index >= total_length) {
                    free(result);
                    return NULL;
                }
                result[index++] = ',';
            }
        }
    }

    result[index] = '\0';
    *output_length = total_length;
    return result;
}

int main() {
    char* tuple1[] = { "apple", "banana", "cherry", NULL };
    char* tuple2[] = { "dog", "cat", NULL };
    char* tuple3[] = { "red", "green", "blue", "yellow", NULL };

    char*** tuple_list = (char***)malloc(3 * sizeof(char**));
    tuple_list[0] = tuple1;
    tuple_list[1] = tuple2;
    tuple_list[2] = tuple3;
    int tuple_count = 3;

    int output_length;
    char* flattened = flatten_tuple_list(tuple_list, tuple_count, &output_length);

    if (flattened != NULL) {
        printf("Flattened list: %s\n", flattened);
        free(flattened);
    } else {
        printf("Memory allocation failed.\n");
    }

    free(tuple_list);
    return 0;
}