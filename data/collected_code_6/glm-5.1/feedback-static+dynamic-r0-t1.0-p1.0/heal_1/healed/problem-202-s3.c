#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_even_chars(const char *str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    size_t new_len = (len + 1) / 2;
    
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 1; i < len; i += 2) {
        result[j++] = str[i];
    }
    
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *original = "abcdefghijklmnopqrstuvwxyz";
    size_t original_max_len = 64;
    char *modified = remove_even_chars(original, original_max_len);
    
    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    }

    return 0;
}