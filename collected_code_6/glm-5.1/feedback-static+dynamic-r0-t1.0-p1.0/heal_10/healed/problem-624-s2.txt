#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == max_len) {
        return (size_t)-1;
    }
    return len;
}

char *string_to_upper(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, 1024 * 1024);
    if (len == (size_t)-1) {
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
    char *converted = string_to_upper(original);

    if (converted != NULL) {
        printf("Original: %s\n", original);
        printf("Upper:    %s\n", converted);
        free(converted);
    } else {
        printf("Failed to process original string.\n");
    }

    const char *valid_test_str = "valid string";
    char *valid_test = string_to_upper(valid_test_str);
    if (valid_test == NULL) {
        printf("Failed to allocate memory for valid string.\n");
    } else {
        printf("Successfully handled non-NULL input: %s\n", valid_test);
        free(valid_test);
    }

    char *null_test = string_to_upper(NULL);
    if (null_test != NULL) {
        free(null_test);
    }

    return 0;
}