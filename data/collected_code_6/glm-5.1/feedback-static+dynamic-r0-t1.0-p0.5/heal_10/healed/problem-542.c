#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }

    size_t alloc_size = len + 1;
    if (alloc_size > SIZE_MAX / sizeof(char)) {
        return NULL;
    }

    char* result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, str, alloc_size);

    for (size_t i = 0; i < len; i++) {
        if (result[i] == ' ' || result[i] == ',' || result[i] == '.') {
            result[i] = ':';
        }
    }

    return result;
}

int main(void) {
    const char* input = "Hello world, this.is a test.";
    char* output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to process string\n");
        return 1;
    }
    
    return 0;
}