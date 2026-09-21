#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strnlen(list[i], 256);
        if (len == 0 || list[i][len-1] != '\0') {
            return NULL;
        }
        total_length += len;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0, offset = 0; i < size; ++i) {
        int len = strnlen(list[i], 256);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result + offset, list[i], len);
        result[offset + len] = '\0';
        offset += len;
    }

    return result;
}

int main() {
    const char *tuple_list[] = {"(1,2)", "(3,4)", "(5,6)"};
    int size = 3;
    char *flattened = flatten_tuple_list(tuple_list, size);

    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}