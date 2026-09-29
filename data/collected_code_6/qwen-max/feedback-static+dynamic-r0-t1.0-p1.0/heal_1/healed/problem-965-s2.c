#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    size_t len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper(str[i])) {
            if (i > 0 && str[i - 1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower(str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *input = "ThisIsACamelCaseString";
    char *converted = camel_to_snake(input);
    if (converted != NULL) {
        printf("%s\n", converted);
        free(converted);
    }
    return 0;
}