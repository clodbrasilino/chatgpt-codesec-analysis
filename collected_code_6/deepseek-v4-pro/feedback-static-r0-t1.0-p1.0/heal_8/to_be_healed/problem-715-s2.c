#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t size;
} Tuple;

Tuple parse_tuple(const char *str) {
    Tuple result = {NULL, 0};
    if (str == NULL) {
        return result;
    }

    size_t len = strnlen(str, 4096);
    if (len < 2 || str[0] != '(' || str[len - 1] != ')') {
        return result;
    }

    size_t content_len = len - 2;
    if (content_len == 0) {
        result.values = (int *)malloc(sizeof(int));
        if (result.values == NULL) {
            return result;
        }
        result.size = 0;
        return result;
    }

    if (content_len > 4096) {
        return result;
    }

    char *copy = (char *)malloc(content_len + 1);
    if (copy == NULL) {
        return result;
    }

    if (content_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str + 1, content_len);
    }
    copy[content_len] = '\0';

    size_t capacity = 8;
    int *values = (int *)malloc(capacity * sizeof(int));
    if (values == NULL) {
        free(copy);
        return result;
    }

    char *saveptr;
    char *token = strtok_r(copy, ",", &saveptr);
    size_t count = 0;

    while (token != NULL) {
        while (*token == ' ') {
            token++;
        }

        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        if (count == capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(int))) {
                free(values);
                free(copy);
                return result;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(int)) {
                free(values);
                free(copy);
                return result;
            }
            int *temp = (int *)realloc(values, new_capacity * sizeof(int));
            if (temp == NULL) {
                free(values);
                free(copy);
                return result;
            }
            values = temp;
            capacity = new_capacity;
        }

        char *endptr;
        errno = 0;
        long val = strtol(token, &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            free(values);
            free(copy);
            return result;
        }

        if (*endptr != '\0' && *endptr != ' ') {
            free(values);
            free(copy);
            return result;
        }

        values[count++] = (int)val;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);

    result.values = values;
    result.size = count;

    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char *input = "(1, 2, 3, 4, 5)";
    Tuple tuple = parse_tuple(input);

    if (tuple.values == NULL && tuple.size != 0) {
        fprintf(stderr, "Failed to parse tuple\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.values[i]);
    }
    printf("\n");

    free_tuple(&tuple);
    return EXIT_SUCCESS;
}