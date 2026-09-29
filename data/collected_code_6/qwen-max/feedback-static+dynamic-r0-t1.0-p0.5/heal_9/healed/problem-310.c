#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;

    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;

    tuple->len = strnlen(input, 1024);
    tuple->str = malloc((tuple->len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    snprintf(tuple->str, tuple->len + 1, "%s", input);
    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *input = "Hello, World!";
    StringTuple *tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("String: %s\n", tuple->str);
        printf("Length: %zu\n", tuple->len);
        free_tuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}