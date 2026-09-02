#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_odd_indexed_chars(const char *input) {
    if (input == NULL) return NULL;
    
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main() {
    const char *input = "Hello, World!";
    char *output = remove_odd_indexed_chars(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}