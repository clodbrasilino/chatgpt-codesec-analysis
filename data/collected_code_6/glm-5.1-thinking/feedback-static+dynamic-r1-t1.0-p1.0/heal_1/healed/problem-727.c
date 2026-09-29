#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *remove_non_alnum(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *p = str;
    while (*p) {
        if (isalnum((unsigned char)*p)) {
            len++;
        }
        p++;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t idx = 0;
    p = str;
    while (*p) {
        if (isalnum((unsigned char)*p)) {
            result[idx++] = *p;
        }
        p++;
    }

    result[idx] = '\0';
    
    return result;
}

int main(void) {
    const char *input = "Hello, World! 123 @#";
    char *output = remove_non_alnum(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}