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
    
    strcpy(tuple->str, input);
    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *inputs[] = {"python 3.0", "item1", "15.10"};
    for (size_t i = 0; i < 3; ++i) {
        StringTuple *result = string_to_tuple(inputs[i]);
        
        if (result != NULL) {
            for (size_t j = 0; j < result->len; ++j) {
                printf("'%c'", result->str[j]);
            }
            printf("\n");
            free_tuple(result);
        } else {
            printf("Failed to convert to tuple.\n");
        }
    }
    return 0;
}