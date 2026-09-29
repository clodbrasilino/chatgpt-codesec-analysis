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

    if (memchr(str, '\0', str_len) != NULL) {
        return NULL;
    }

    result = (char *)malloc(str_len + 1);
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(original);
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