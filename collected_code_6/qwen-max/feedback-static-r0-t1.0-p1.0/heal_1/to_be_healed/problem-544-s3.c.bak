#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  expected 'char ***' but argument is of type 'char ****'
 */
char* flatten_tuple_list(char*** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][j] != NULL; ++j) {
            total_length += strlen(tuple_list[i][j]) + 1; // Add 1 for comma or space
        }
    }
    --total_length; // Remove the last extra comma or space

    char* result = (char*) malloc(total_length + 1);
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i][j] != NULL; ++j) {
            int len = strlen(tuple_list[i][j]);
            strncpy(result + index, tuple_list[i][j], len);
            index += len;
            if (tuple_list[i][j + 1] != NULL || (tuple_list[i + 1] != NULL && tuple_list[i + 1][0] != NULL)) {
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
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple1[1]')
     *  (near initialization for 'tuple1[0]')
     */
    char** tuple1[] = { "apple", "banana", "cherry", NULL };
    /* Possible weaknesses found:
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple2[1]')
     *  (near initialization for 'tuple2[0]')
     */
    char** tuple2[] = { "dog", "cat", NULL };
    /* Possible weaknesses found:
     *  initialization of 'char **' from incompatible pointer type 'char *' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuple3[2]')
     *  (near initialization for 'tuple3[0]')
     *  (near initialization for 'tuple3[1]')
     *  (near initialization for 'tuple3[3]')
     */
    char** tuple3[] = { "red", "green", "blue", "yellow", NULL };

    char*** tuple_list[] = { tuple1, tuple2, tuple3, NULL };
    int tuple_count = 3;

    int output_length;
    /* Possible weaknesses found:
     *  passing argument 1 of 'flatten_tuple_list' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    char* flattened = flatten_tuple_list(tuple_list, tuple_count, &output_length);

    if (flattened != NULL) {
        printf("Flattened list: %s\n", flattened);
        free(flattened);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}