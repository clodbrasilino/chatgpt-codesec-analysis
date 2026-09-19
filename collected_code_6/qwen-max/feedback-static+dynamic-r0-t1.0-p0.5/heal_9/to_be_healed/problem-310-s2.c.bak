#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["python 3.0","
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

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
    const char *input[] = {"python3.0", "15.10", "item1", "Hello, World!"};
    for (size_t i = 0; i < 4; ++i) {
        StringTuple *tuple = string_to_tuple(input[i]);
        if (tuple != NULL) {
            printf("[");
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c'", tuple->str[j]);
                if (j < tuple->len - 1) printf(", ");
            }
            printf("]\n");
            free_tuple(tuple);
        } else {
            printf("Failed to create tuple.\n");
        }
    }
    return 0;
}