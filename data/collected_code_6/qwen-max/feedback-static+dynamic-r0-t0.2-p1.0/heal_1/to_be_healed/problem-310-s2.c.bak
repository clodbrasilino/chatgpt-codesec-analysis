#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["python 3.0","
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;
    
    tuple->len = strlen(input);
    tuple->str = (char *)malloc(tuple->len + 1);
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
    const char *input = "Hello, World!";
    StringTuple *tuple = string_to_tuple(input);
    
    if (tuple != NULL) {
        printf("Tuple: %s, Length: %zu\n", tuple->str, tuple->len);
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to create tuple.\n");
    }
    
    return 0;
}