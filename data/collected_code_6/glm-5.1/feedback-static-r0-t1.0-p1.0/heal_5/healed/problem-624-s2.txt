#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *string_to_upper(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, SIZE_MAX);
    char *upper_str = malloc(len + 1);
    if (upper_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        upper_str[i] = (char)toupper((unsigned char)str[i]);
    }
    upper_str[len] = '\0';

    return upper_str;
}

int main(void) {
    const char *original = "Hello, World! 123";
    char *converted = string_to_upper(original);

    if (converted != NULL) {
        printf("Original: %s\n", original);
        printf("Upper:    %s\n", converted);
        free(converted);
    }

    char *null_test = string_to_upper(NULL);

    if (null_test == NULL) {
        printf("Successfully handled NULL input.\n");
    } else {
        free(null_test);
    }

    return 0;
}