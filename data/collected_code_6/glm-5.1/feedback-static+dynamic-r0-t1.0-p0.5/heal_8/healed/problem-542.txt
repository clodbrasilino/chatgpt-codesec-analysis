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

    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, str, len + 1);

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