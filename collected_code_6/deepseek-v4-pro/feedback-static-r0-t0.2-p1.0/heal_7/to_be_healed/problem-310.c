#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.count = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = strnlen(str, 1024);
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || len >= 1024) {
        return tuple;
    }

    char *copy = malloc(len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return tuple;
    }

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    copy[len] = '\0';

    size_t capacity = 4;
    tuple.elements = malloc(capacity * sizeof(char *));
    if (tuple.elements == NULL) {
        free(copy);
        return tuple;
    }

    char *saveptr;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (*token == ' ') token++;
        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        char *end = token;
        while (*end != '\0') end++;
        end--;
        while (end > token && *end == ' ') {
            end--;
        }
        *(end + 1) = '\0';

        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        size_t token_len = end + 1 - token;

        if (tuple.count == capacity) {
            if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            capacity *= 2;
            char **new_elements = realloc(tuple.elements, capacity * sizeof(char *));
            if (new_elements == NULL) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.elements = new_elements;
        }

        tuple.elements[tuple.count] = malloc(token_len + 1);
        if (tuple.elements[tuple.count] == NULL) {
            for (size_t i = 0; i < tuple.count; i++) {
                free(tuple.elements[i]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }

        if (token_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple.elements[tuple.count], token, token_len);
        }
        tuple.elements[tuple.count][token_len] = '\0';
        tuple.count++;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    tuple->elements = NULL;
    tuple->count = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(input);

    if (result.elements == NULL && result.count == 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple elements (%zu):\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] = '%s'\n", i, result.elements[i]);
    }

    free_tuple(&result);
    return EXIT_SUCCESS;
}