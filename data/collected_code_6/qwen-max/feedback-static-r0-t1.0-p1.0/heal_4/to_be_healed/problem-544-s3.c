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
            total_length += len + 1;
        }
    }
    if (total_length > 0) --total_length;

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
    char* tuple1[] = { "apple", "banana", "cherry", NULL };
    char* tuple2[] = { "dog", "cat", NULL };
    char* tuple3[] = { "red", "green", "blue", "yellow", NULL };

    char**** tuple_list = (char****)malloc(3 * sizeof(char***));
    /* Possible weaknesses found:
     *  assignment to 'char ***' from incompatible pointer type 'char * (*)[4]' [-Wincompatible-pointer-types]
     */
    tuple_list[0] = &tuple1;
    /* Possible weaknesses found:
     *  assignment to 'char ***' from incompatible pointer type 'char * (*)[3]' [-Wincompatible-pointer-types]
     */
    tuple_list[1] = &tuple2;
    /* Possible weaknesses found:
     *  assignment to 'char ***' from incompatible pointer type 'char * (*)[5]' [-Wincompatible-pointer-types]
     */
    tuple_list[2] = &tuple3;
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