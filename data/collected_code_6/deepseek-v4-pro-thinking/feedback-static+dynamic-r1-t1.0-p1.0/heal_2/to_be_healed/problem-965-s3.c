#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }
    if (len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }
    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            if (j > 0) {
                result[j++] = '_';
            }
            result[j++] = (char)tolower(c);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main(void) {
    const char *camel = "camelCaseString";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    char *snake = camel_to_snake(camel, len);
    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    }
    return 0;
}