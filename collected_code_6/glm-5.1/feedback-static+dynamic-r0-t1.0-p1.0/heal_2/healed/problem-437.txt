#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_chars(const char *str, size_t str_len) {
    size_t new_len;
    char *result;
    size_t i;
    size_t j;

    if (str == NULL) {
        return NULL;
    }

    new_len = (str_len + 1) / 2;

    result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < str_len; i += 2) {
        result[j++] = str[i];
    }

    result[j] = '\0';

    return result;
}

int main(void) {
    const char *original = "abcdefghijklmnopqrstuvwxyz";
    size_t len = strnlen(original, 256);
    char *filtered = remove_odd_chars(original, len);

    if (filtered != NULL) {
        printf("Original: %s\n", original);
        printf("Filtered: %s\n", filtered);
        free(filtered);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    filtered = remove_odd_chars(NULL, 0);
    if (filtered == NULL) {
        printf("Successfully handled NULL input\n");
    }

    return 0;
}