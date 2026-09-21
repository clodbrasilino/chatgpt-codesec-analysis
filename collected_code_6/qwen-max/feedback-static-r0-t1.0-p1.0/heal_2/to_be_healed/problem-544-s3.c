#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char**** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; (*tuple_list)[i][j] != NULL; ++j) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen((*tuple_list)[i][j]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
    /* Possible weaknesses found:
     *  (near initialization for 'tuple1[2]')
     *  (near initialization for 'tuple1[1]')
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple1[0]')
     */
    char** tuple1[] = { "apple", "banana", "cherry", NULL };
    /* Possible weaknesses found:
     *  (near initialization for 'tuple2[1]')
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple2[0]')
     */
    char** tuple2[] = { "dog", "cat", NULL };
    /* Possible weaknesses found:
     *  (near initialization for 'tuple3[2]')
     *  (near initialization for 'tuple3[1]')
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple3[3]')
     *  (near initialization for 'tuple3[0]')
     */
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