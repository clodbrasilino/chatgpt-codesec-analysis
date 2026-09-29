#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *remove_lowercase(const char *str, size_t len) {
    if (str == NULL || len == (size_t)-1) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_len = 0;
    for (size_t i = 0; i < len && str[i] != '\0'; ++i) {
        if (!islower((unsigned char)str[i])) {
            result[res_len++] = str[i];
        }
    }
    result[res_len] = '\0';

    return result;
}

int main(void) {
    const char input[] = "HelloWorld123abcXYZ";
    char *result = remove_lowercase(input, sizeof(input) - 1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}