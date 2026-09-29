#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    size_t len = strnlen(input, 1024);
    
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;
    
    tuple->str = (char *)malloc((len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->len = len;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->str, input, len * sizeof(char));
    tuple->str[len] = '\0';
    
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
    StringTuple *result = string_to_tuple(input);

    if (result != NULL) {
        printf("Converted to tuple: %s\n", result->str);
        free_tuple(result);
    } else {
        printf("Failed to convert to tuple.\n");
    }

    return 0;
}