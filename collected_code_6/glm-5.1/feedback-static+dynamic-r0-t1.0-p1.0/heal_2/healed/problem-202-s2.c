#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_even_chars(const char *str, size_t str_len) {
    size_t j;
    size_t i;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    result = (char *)malloc(str_len / 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 1; i < str_len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *original = "abcdefg";
    size_t len = 0;
    while (original[len] != '\0') {
        len++;
    }
    char *modified = remove_even_chars(original, len);
    
    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    }

    modified = remove_even_chars(NULL, 0);
    if (modified == NULL) {
        printf("Successfully handled NULL input\n");
    }

    return 0;
}