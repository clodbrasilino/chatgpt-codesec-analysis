#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index(const char *str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklm";
    size_t input_max_len = 256;
    char *output = remove_odd_index(input, input_max_len);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}