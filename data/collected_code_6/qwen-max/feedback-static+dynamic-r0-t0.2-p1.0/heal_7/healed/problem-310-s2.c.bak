#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    
    size_t len = strlen(input);
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;
    
    tuple->len = len;
    tuple->str = (char *)malloc((len + 1) * sizeof(char));
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
    const char *inputs[] = {"python3.0", "item1", "15.10", NULL, ""};
    for (int i = 0; i < 5; ++i) {
        const char *input = inputs[i];
        StringTuple *tuple = string_to_tuple(input);
        
        if (tuple != NULL) {
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c'", tuple->str[j]);
            }
            printf("\n");
            free_tuple(tuple);
        } else {
            if (input == NULL) {
                fprintf(stderr, "Input is NULL.\n");
            } else {
                fprintf(stderr, "Failed to create tuple.\n");
            }
        }
    }
    
    return 0;
}