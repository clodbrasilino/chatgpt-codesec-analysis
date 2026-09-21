#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alnum(const char *str, size_t len) {
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    
    char *output = remove_non_alnum(input, input_len);
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}