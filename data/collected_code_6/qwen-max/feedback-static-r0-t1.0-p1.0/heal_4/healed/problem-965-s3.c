#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

char *camel_to_snake(char *str) {
    size_t len = strlen(str);
    char *result = (char *)malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) return NULL;

    bool add_underscore = false;
    int j = 0;

    for (size_t i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && !add_underscore) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
            add_underscore = true;
        } else {
            result[j++] = str[i];
            add_underscore = false;
        }
    }
    result[j] = '\0';

    strcpy(str, result);
    free(result);
    return str;
}

int main() {
    char str[256];
    printf("Enter a camel case string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0'; // remove newline
        camel_to_snake(str);
        printf("Snake case: %s\n", str);
    }
    return 0;
}