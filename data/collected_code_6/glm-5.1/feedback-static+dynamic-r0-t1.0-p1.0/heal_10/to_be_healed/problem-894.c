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
    memcpy(buffer, str + 1, buffer_size - 1);
    buffer[buffer_size - 1] = '\0';

    char *comma = strchr(buffer, ',');
    if (comma == NULL) {
        free(buffer);
        return -1;
    }

    *comma = '\0';
    char *second_str = comma + 1;

    size_t first_len = (size_t)(comma - buffer);
    if (first_len >= buffer_size) {
        free(buffer);
        return -1;
    }

    char *first_buf = (char *)malloc(first_len + 1);
    if (first_buf == NULL) {
        free(buffer);
        return -1;
    }
    snprintf(first_buf, first_len + 1, "%s", buffer);

    size_t second_len = strnlen(second_str, buffer_size - first_len - 1);
    char *second_buf = (char *)malloc(second_len + 1);
    if (second_buf == NULL) {
        free(first_buf);
        free(buffer);
        return -1;
    }
    snprintf(second_buf, second_len + 1, "%s", second_str);

    free(buffer);

    char *end_ptr1 = NULL;
    char *end_ptr2 = NULL;

    float val1 = strtof(first_buf, &end_ptr1);
    float val2 = strtof(second_buf, &end_ptr2);

    int parse_ok = 1;
    if (end_ptr1 == first_buf || *end_ptr1 != '\0' || end_ptr2 == second_buf || *end_ptr2 != '\0') {
        parse_ok = 0;
    }

    if (parse_ok) {
        out->first = val1;
        out->second = val2;
    }

    free(first_buf);
    free(second_buf);

    return parse_ok ? 0 : -1;
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