#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return tuple;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, str);

    size_t capacity = 4;
    tuple.elements = malloc(capacity * sizeof(char *));
    if (tuple.elements == NULL) {
        free(copy);
        return tuple;
    }

    char *token = strtok(copy, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        *(end + 1) = '\0';

        if (tuple.count == capacity) {
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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        tuple.elements[tuple.count] = malloc(strlen(token) + 1);
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
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tuple.elements[tuple.count], token);
        tuple.count++;
        token = strtok(NULL, ",");
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