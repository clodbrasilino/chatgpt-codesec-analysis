#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
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
    char *snake = camel_to_snake(camel);
    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    }
    return 0;
}