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

    size_t res_idx = 0;
    const char* p = str;

    while (*p) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            result[res_idx++] = ':';
            p++;
        } else {
            result[res_idx++] = *p++;
        }
    }
    result[res_idx] = '\0';

    return result;
}

int main(void) {
    const char* input = "Hello world, this.is a test.";
    char* output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}