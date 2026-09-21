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

    /* Possible weaknesses found:
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err = memcpy_s(result, len + 1, str, len + 1);
    if (err != 0) {
        free(result);
        return NULL;
    }

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