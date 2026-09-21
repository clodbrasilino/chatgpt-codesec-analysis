#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char**** tuple_list, int tuple_count, int* output_length) {
    int total_length = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i] != NULL && (*tuple_list[i])[j] != NULL; ++j) {
            size_t len = strnlen((*tuple_list[i])[j], 1024);
            total_length += (len >= 2) ? len : 1;
        }
    }
    --total_length;

    char* result = (char*) malloc(total_length + 1);
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; ++i) {
        for (int j = 0; tuple_list[i] != NULL && (*tuple_list[i])[j] != NULL; ++j) {
            size_t len = strnlen((*tuple_list[i])[j], 1024);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result + index, (*tuple_list[i])[j], len);
            index += len;
            if ((*tuple_list[i])[j + 1] != NULL || (i + 1 < tuple_count && (*tuple_list[i + 1])[0] != NULL)) {
                result[index++] = ',';
            }
        }
    }

    result[index] = '\0';
    *output_length = total_length;
    return result;
}

int main() {
    char* tuple1[] = { "apple", "banana", "cherry" };
    char* tuple2[] = { "dog", "cat" };
    char* tuple3[] = { "red", "green", "blue", "yellow" };

    char*** tuple_list[] = { (char***)&tuple1, (char***)&tuple2, (char***)&tuple3 };
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