#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}