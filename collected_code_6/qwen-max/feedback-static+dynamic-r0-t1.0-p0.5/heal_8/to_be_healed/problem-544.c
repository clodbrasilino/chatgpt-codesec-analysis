#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size, char delimiter) {
    if (size <= 0) return NULL;
    
    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strnlen(list[i], 1024);
        if (len == 0 && strcmp(list[i], "") != 0) return NULL;
        total_length += len;
    }
    total_length += size - 1; // for delimiters
    total_length += 1; // for null terminator

    char *result = (char *)malloc(total_length * sizeof(char));
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strnlen(list[i], 1024);
        if (len == 0 && strcmp(list[i], "") != 0) return NULL;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result + index, list[i], len);
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