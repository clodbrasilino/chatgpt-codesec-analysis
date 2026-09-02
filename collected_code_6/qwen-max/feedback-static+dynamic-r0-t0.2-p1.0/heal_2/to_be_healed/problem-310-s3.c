#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["python 3.0","
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
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

    for (size_t i = 0; i < tuple->len; ++i) {
        tuple->str[i] = input[i];
    }
    tuple->str[tuple->len] = '\0';

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
            printf("Tuple: ");
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("%c, ", tuple->str[j]);
            }
            printf("(Length: %zu)\n", tuple->len);
            free_tuple(tuple);
        } else {
            printf("Failed to create tuple.\n");
        }
    }
    return 0;
}