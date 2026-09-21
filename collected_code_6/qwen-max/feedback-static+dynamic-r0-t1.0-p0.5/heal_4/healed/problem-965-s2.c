#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* camel_to_snake(const char *str) {
    if (str == NULL) return NULL;

    int len = 0;
    const char *p = str;
    while (*p) {
        len++;
        p++;
    }

    char *result = (char *)malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int i = 0;
    for (int j = 0; str[j]; j++) {
        if (isupper((unsigned char)str[j])) {
            if (i > 0 && result[i-1] != '_') {
                result[i++] = '_';
            }
            result[i++] = tolower((unsigned char)str[j]);
        } else {
            result[i++] = str[j];
        }
    }
    result[i] = '\0';

    return result;
}

int main() {
    const char input[] = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        printf("Error: Output is NULL\n");
    }
    return 0;
}