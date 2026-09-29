#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char**** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; (*tuple_list)[i][j] != NULL; ++j) {
            size_t len = strlen((*tuple_list)[i][j]);
            total_length += len + 1; // Add 1 for comma or space
        }
    }
    if (total_length > 0) --total_length; // Remove the last extra comma or space

    char* result = (char*) malloc(total_length + 1);
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; (*tuple_list)[i][j] != NULL; ++j) {
            size_t len = strlen((*tuple_list)[i][j]);
            memcpy(result + index, (*tuple_list)[i][j], len);
            index += len;
            if ((*tuple_list)[i][j + 1] != NULL || (i + 1 < tuple_count && (*tuple_list)[i + 1][0] != NULL)) {
                result[index++] = ',';
            }
        }
    }

    result[index] = '\0';
    *output_length = total_length;
    return result;
}

int main() {
    char** tuple1[] = { "apple", "banana", "cherry", NULL };
    char** tuple2[] = { "dog", "cat", NULL };
    char** tuple3[] = { "red", "green", "blue", "yellow", NULL };

    char**** tuple_list = (char****) &tuple1;
    int tuple_count = 3;

    int output_length;
    char* flattened = flatten_tuple_list(tuple_list, tuple_count, &output_length);

    if (flattened != NULL) {
        printf("Flattened list: %s\n", flattened);
        free(flattened);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}