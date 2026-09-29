#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple);
Tuple* string_to_tuple(const char *str);
void print_tuple(const Tuple *tuple);

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->elements = NULL;
    tuple->count = 0;

    const char *p = str;
    while (*p && (*p == '(' || isspace((unsigned char)*p))) {
        p++;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(p);
    const char *end_str = p + len - 1;
    while (end_str >= p && (*end_str == ')' || isspace((unsigned char)*end_str))) {
        end_str--;
    }

    if (p > end_str) {
        return tuple;
    }

    while (p <= end_str) {
        const char *start_elem = p;
        while (p <= end_str && *p != ',') {
            p++;
        }
        const char *end_elem = p - 1;

        while (start_elem <= end_elem && isspace((unsigned char)*start_elem)) {
            start_elem++;
        }
        while (end_elem >= start_elem && isspace((unsigned char)*end_elem)) {
            end_elem--;
        }

        size_t elem_len = (start_elem <= end_elem) ? (size_t)(end_elem - start_elem + 1) : 0;

        char *elem_str = (char *)malloc(elem_len + 1);
        if (!elem_str) {
            free_tuple(tuple);
            return NULL;
        }

        if (elem_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(elem_str, start_elem, elem_len);
        }
        elem_str[elem_len] = '\0';

        char **new_elements = (char **)realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            free(elem_str);
            free_tuple(tuple);
            return NULL;
        }
        tuple->elements = new_elements;
        tuple->elements[tuple->count] = elem_str;
        tuple->count++;

        if (p <= end_str && *p == ',') {
            p++;
        }
    }

    return tuple;
}

void print_tuple(const Tuple *tuple) {
    if (!tuple) {
        return;
    }
    printf("Tuple elements: %zu\n", tuple->count);
    for (size_t i = 0; i < tuple->count; i++) {
        printf("  [%zu]: \"%s\"\n", i, tuple->elements[i]);
    }
}

int main(void) {
    const char *input = "( apple, banana , cherry, date )";
    Tuple *tuple = string_to_tuple(input);

    if (tuple) {
        print_tuple(tuple);
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}