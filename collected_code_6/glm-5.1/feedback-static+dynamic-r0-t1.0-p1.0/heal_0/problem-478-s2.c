#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* remove_lowercase_substrings(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (islower((unsigned char)str[i])) {
            while (str[i] != '\0' && islower((unsigned char)str[i])) {
                i++;
            }
        } else {
            while (str[i] != '\0' && !islower((unsigned char)str[i])) {
                result[res_idx++] = str[i];
                i++;
            }
        }
    }

    result[res_idx] = '\0';

    char* shrunk = (char*)realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main() {
    const char* input = "AbcDEFghiJKLmnopQRS";
    char* output = remove_lowercase_substrings(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}