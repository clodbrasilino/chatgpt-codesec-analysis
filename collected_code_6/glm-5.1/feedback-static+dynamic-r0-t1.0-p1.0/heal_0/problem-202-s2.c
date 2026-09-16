#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_even_chars(const char *str) {
    size_t len;
    char *result;
    size_t j;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 1; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *original = "abcdefg";
    char *modified = remove_even_chars(original);
    
    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    }

    modified = remove_even_chars(NULL);
    if (modified == NULL) {
        printf("Successfully handled NULL input\n");
    }

    return 0;
}