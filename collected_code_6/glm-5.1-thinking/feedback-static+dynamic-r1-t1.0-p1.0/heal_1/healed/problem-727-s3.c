#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *remove_non_alnum(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }
    
    size_t result_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalnum((unsigned char)str[i])) {
            result[result_idx++] = str[i];
        }
    }
    
    result[result_idx] = '\0';
    return result;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$%";
    char *output = remove_non_alnum(input);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}