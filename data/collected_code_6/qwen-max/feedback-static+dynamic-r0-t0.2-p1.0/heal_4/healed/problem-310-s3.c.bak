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
    const char *inputs[] = {"python3.0", "item1", "15.10"};
    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); ++i) {
        StringTuple *tuple = string_to_tuple(inputs[i]);
        if (tuple != NULL) {
            printf("['");
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("%c", tuple->str[j]);
                if (j < tuple->len - 1) {
                    printf("', '");
                }
            }
            printf("'] (Length: %zu)\n", tuple->len);
            free_tuple(tuple);
        } else {
            printf("Failed to create tuple.\n");
        }
    }
    return 0;
}