#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096
#define MAX_ELEMENT_LEN 4096

typedef struct {
    char **elements;
    size_t size;
} Tuple;

static void cleanup_elements(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.size = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = strnlen(str, MAX_STRING_LEN);
    if (len == 0) {
        return tuple;
    }

    tuple.elements = (char **)malloc(sizeof(char *));
    if (tuple.elements == NULL) {
        return tuple;
    }

    size_t start = 0;
    size_t i;
    int in_quotes = 0;
    char quote_char = '\0';

    for (i = 0; i <= len; i++) {
        if (in_quotes) {
            if (str[i] == quote_char && i > 0 && str[i-1] != '\\') {
                in_quotes = 0;
            }
        } else {
            if (str[i] == '"' || str[i] == '\'') {
                in_quotes = 1;
                quote_char = str[i];
            } else if (str[i] == ',' || str[i] == '\0') {
                size_t elem_len = i - start;
                if (elem_len > MAX_ELEMENT_LEN) {
                    cleanup_elements(&tuple);
                    return tuple;
                }
                if (start + elem_len > len) {
                    cleanup_elements(&tuple);
                    return tuple;
                }
                
                char *element = (char *)malloc(elem_len + 1);
                if (element == NULL) {
                    cleanup_elements(&tuple);
                    return tuple;
                }
                
                if (elem_len > 0) {
                    memcpy(element, str + start, elem_len);
                }
                element[elem_len] = '\0';

                char **new_elements = (char **)realloc(tuple.elements, (tuple.size + 1) * sizeof(char *));
                if (new_elements == NULL) {
                    free(element);
                    cleanup_elements(&tuple);
                    return tuple;
                }
                tuple.elements = new_elements;
                tuple.elements[tuple.size] = element;
                tuple.size++;

                if (str[i] == '\0') {
                    break;
                }
                start = i + 1;
                while (start < len && str[start] == ' ') {
                    start++;
                }
            }
        }
    }

    if (tuple.size == 0 && tuple.elements != NULL) {
        free(tuple.elements);
        tuple.elements = NULL;
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    cleanup_elements(tuple);
}

int main(void) {
    const char *test_string = "hello, world, 'foo,bar', \"baz,qux\", ";
    Tuple result = string_to_tuple(test_string);

    printf("Tuple size: %zu\n", result.size);
    for (size_t i = 0; i < result.size; i++) {
        printf("Element %zu: %s\n", i, result.elements[i]);
    }

    free_tuple(&result);
    return 0;
}