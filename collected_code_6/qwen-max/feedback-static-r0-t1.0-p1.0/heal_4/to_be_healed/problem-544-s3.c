#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char**** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][0][j] != NULL; ++j) {
            total_length += strlen(tuple_list[i][0][j]) + 1; 
        }
    }
    --total_length;

    char* result = (char*) malloc(total_length + 1);
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][0][j] != NULL; ++j) {
            int len = strlen(tuple_list[i][0][j]);
            strncpy(result + index, tuple_list[i][0][j], len);
            index += len;
            if (tuple_list[i][0][j + 1] != NULL || (i + 1 < tuple_count && tuple_list[i + 1][0][0] != NULL)) {
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

    /* Possible weaknesses found:
     *  initialization of 'char ***' from incompatible pointer type 'char * (*)[4]' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple_list[1]')
     *  (near initialization for 'tuple_list[0]')
     *  initialization of 'char ***' from incompatible pointer type 'char * (*)[5]' [-Wincompatible-pointer-types]
     *  initialization of 'char ***' from incompatible pointer type 'char * (*)[3]' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple_list[2]')
     */
    char*** tuple_list[4] = { &tuple1, &tuple2, &tuple3, NULL };
    int tuple_count = 3;

    int output_length;
    char* flattened = flatten_tuple_list((char****)tuple_list, tuple_count, &output_length);

    if (flattened != NULL) {
        printf("Flattened list: %s\n", flattened);
        free(flattened);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}