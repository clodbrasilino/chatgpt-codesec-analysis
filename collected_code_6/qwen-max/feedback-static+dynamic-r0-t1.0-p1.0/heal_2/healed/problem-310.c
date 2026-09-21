#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;

StringTuple *stringToTuple(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    size_t len = 0;
    while (input[len]) {
        len++;
    }
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->len = len;
    tuple->str = (char *)malloc((len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        tuple->str[i] = input[i];
    }
    tuple->str[len] = '\0';
    return tuple;
}

void freeTuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *input = "Hello, World!";
    StringTuple *tuple = stringToTuple(input);
    if (tuple != NULL) {
        printf("Converted to tuple: %s\n", tuple->str);
        freeTuple(tuple);
    } else {
        fprintf(stderr, "Failed to create tuple\n");
    }
    return 0;
}