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
    size_t len = strlen(input);
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
    strcpy(tuple->str, input);
    return tuple;
}

void freeTuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *inputs[] = {"python3.0", "item1", "15.10", "Hello, World!"};
    for (size_t i = 0; i < 4; ++i) {
        StringTuple *tuple = stringToTuple(inputs[i]);
        if (tuple != NULL) {
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c' ", tuple->str[j]);
            }
            printf("\n");
            freeTuple(tuple);
        } else {
            fprintf(stderr, "Failed to create tuple\n");
        }
    }
    return 0;
}