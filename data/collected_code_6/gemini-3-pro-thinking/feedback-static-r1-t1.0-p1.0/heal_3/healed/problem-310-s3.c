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

    const char *start = str;
    while (*start != '\0' && (isspace((unsigned char)*start) || *start == '(')) {
        start++;
    }

    const char *end = start;
    while (*end != '\0') {
        end++;
    }
    if (end > start) {
        end--;
    }
    while (end >= start && (isspace((unsigned char)*end) || *end == ')')) {
        end--;
    }

    if (start > end) {
        return tuple;
    }

    const char *p = start;
    while (p <= end) {
        const char *elem_start = p;
        while (p <= end && *p != ',') {
            p++;
        }
        
        const char *elem_end = p - 1;
        while (elem_start <= elem_end && isspace((unsigned char)*elem_start)) {
            elem_start++;
        }
        while (elem_end >= elem_start && isspace((unsigned char)*elem_end)) {
            elem_end--;
        }

        size_t len = 0;
        if (elem_end >= elem_start) {
            len = (size_t)(elem_end - elem_start + 1);
        }

        char *elem_str = (char *)malloc(len + 1);
        if (!elem_str) {
            free_tuple(tuple);
            return NULL;
        }

        for (size_t i = 0; i < len; i++) {
            elem_str[i] = elem_start[i];
        }
        elem_str[len] = '\0';

        char **new_elements = (char **)realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            free(elem_str);
            free_tuple(tuple);
            return NULL;
        }
        tuple->elements = new_elements;
        tuple->elements[tuple->count] = elem_str;
        tuple->count++;

        if (p <= end && *p == ',') {
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