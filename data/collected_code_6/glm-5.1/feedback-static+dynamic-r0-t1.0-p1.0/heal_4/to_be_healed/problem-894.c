#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float first;
    float second;
} Tuple;

int string_to_tuple(const char *str, Tuple *out) {
    if (str == NULL || out == NULL) {
        return -1;
    }

    size_t len = strnlen(str, 256);
    if (len < 3 || len >= 256) {
        return -1;
    }

    if (str[0] != '(' || str[len - 1] != ')') {
        return -1;
    }

    size_t buffer_size = len - 1;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, str + 1, len - 2);
    buffer[len - 2] = '\0';

    char *comma = strchr(buffer, ',');
    if (comma == NULL) {
        free(buffer);
        return -1;
    }

    *comma = '\0';
    char *second_str = comma + 1;

    char *end_ptr1 = NULL;
    char *end_ptr2 = NULL;

    float val1 = strtof(buffer, &end_ptr1);
    float val2 = strtof(second_str, &end_ptr2);

    if (end_ptr1 == buffer || *end_ptr1 != '\0' || end_ptr2 == second_str || *end_ptr2 != '\0') {
        free(buffer);
        return -1;
    }

    out->first = val1;
    out->second = val2;

    free(buffer);
    return 0;
}

int main() {
    const char *input = "(3.14,2.71)";
    Tuple t;

    if (string_to_tuple(input, &t) == 0) {
        printf("Tuple: (%.2f, %.2f)\n", t.first, t.second);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}