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
    while (*p != '\0' && (*p == '(' || isspace((unsigned char)*p))) {
        p++;
    }

    const char *end_str = p;
    while (*end_str != '\0') {
        end_str++;
    }

    if (end_str == p) {
        return tuple;
    }
    end_str--;

    while (end_str >= p && (*end_str == ')' || isspace((unsigned char)*end_str))) {
        if (end_str == p) {
            return tuple;
        }
        end_str--;
    }

    while (p <= end_str) {
        const char *start_elem = p;
        while (p <= end_str && *p != ',') {
            p++;
        }
        
        const char *temp_end = p;
        while (start_elem < temp_end && isspace((unsigned char)*start_elem)) {
            start_elem++;
        }
        
        while (temp_end > start_elem && isspace((unsigned char)*(temp_end - 1))) {
            temp_end--;
        }

        size_t elem_len = (size_t)(temp_end - start_elem);
        char *elem_str = (char *)malloc(elem_len + 1);
        
        if (!elem_str) {
            free_tuple(tuple);
            return NULL;
        }

        if (elem_len > 0) {
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