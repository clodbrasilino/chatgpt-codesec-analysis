#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *remove_even_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t new_len = (len + 1) / 2;
    char *result = (char *)malloc(new_len + 1);
    
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
    const char *test_str = "abcdefghij";
    char *result = remove_even_chars(test_str);

    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("After removing even chars: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input\n");
        return 1;
    }

    return 0;
}