#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size, char delimiter) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        total_length += strnlen(list[i], 1024);
    }
    total_length += (size - 1); 
    total_length += 1; 

    char *result = (char *)malloc(total_length * sizeof(char));
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < size; ++i) {
        const size_t len = strnlen(list[i], 1024);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + index, list[i], len);
        index += len;
        if (i < size - 1) {
            result[index++] = delimiter;
        }
    }
    result[index] = '\0';

    return result;
}

int main() {
    const char *tuple_list[] = {"one", "two", "three"};
    int size = 3;
    char delimiter = ',';
    char *flattened = flatten_tuple_list(tuple_list, size, delimiter);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten the tuple list.\n");
    }
    return 0;
}