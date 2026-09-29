#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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
    if (len == 4096 || len < 2 || str[0] != '(' || str[len - 1] != ')') {
        return result;
    }

    size_t inner_len = len - 2;
    char *copy = (char *)malloc(inner_len + 1);
    if (copy == NULL) {
        return result;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str + 1, inner_len);
    copy[inner_len] = '\0';

    size_t capacity = 8;
    int *values = (int *)malloc(capacity * sizeof(int));
    if (values == NULL) {
        free(copy);
        return result;
    }

    char *saveptr = NULL;
    char *token = strtok_r(copy, ",", &saveptr);
    size_t count = 0;

    while (token != NULL) {
        while (*token == ' ') {
            token++;
        }

        if (*token == '\0') {
            break;
        }

        if (count == capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(values, capacity * sizeof(int));
            if (temp == NULL) {
                free(values);
                free(copy);
                return result;
            }
            values = temp;
        }

        char *endptr = NULL;
        errno = 0;
        long val = strtol(token, &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            free(values);
            free(copy);
            result.values = NULL;
            result.size = 0;
            return result;
        }

        if (*endptr != '\0' && *endptr != ' ') {
            free(values);
            free(copy);
            result.values = NULL;
            result.size = 0;
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

    if (tuple.values == NULL) {
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