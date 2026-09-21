#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    
    size_t input_len = strnlen(input, 512);
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;
    
    tuple->len = input_len;
    tuple->str = (char *)malloc((tuple->len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(tuple->str, input, tuple->len);
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