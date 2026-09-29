#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *string_to_upper(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

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
    size_t original_len = strlen(original);
    char *converted = string_to_upper(original, original_len);

    if (converted != NULL) {
        printf("Original: %s\n", original);
        printf("Upper:    %s\n", converted);
        free(converted);
        converted = NULL;
    }

    char *null_test = string_to_upper(NULL, 0);

    if (null_test != NULL) {
        free(null_test);
    }

    return 0;
}