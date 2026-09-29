#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    size_t len = strnlen(input, 1024);
    
    char *output = remove_odd_index_chars(input, len);
    
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);
    
    return 0;
}