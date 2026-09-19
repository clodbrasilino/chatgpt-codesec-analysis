#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;

    tuple->len = strlen(input);
    tuple->str = (char *)malloc((tuple->len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    memcpy(tuple->str, input, tuple->len + 1);

    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *input[] = {"python 3.0", "15.10", "item1", "Hello, World!"};
    for (size_t i = 0; i < 4; ++i) {
        StringTuple *tuple = string_to_tuple(input[i]);

        if (tuple != NULL) {
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c' ", tuple->str[j]);
            }
            printf("\n");
            free_tuple(tuple);
        } else {
            printf("Failed to create tuple.\n");
        }
    }

    return 0;
}