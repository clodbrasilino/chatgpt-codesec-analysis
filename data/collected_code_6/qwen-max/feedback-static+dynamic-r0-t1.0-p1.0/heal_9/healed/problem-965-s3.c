#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    if (len == 0) return strdup("");
    char *result = malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (j > 0 && result[j - 1] != '_') {
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
    char *str = malloc(256 * sizeof(char));
    if (str == NULL) {
        return 1;
    }
    printf("Enter a camel case string: ");
    if (fgets(str, 256, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        char *snake_case_str = camel_to_snake(str);
        if (snake_case_str != NULL) {
            printf("Snake case: %s\n", snake_case_str);
            free(snake_case_str);
        } else {
            printf("Error converting string.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
    free(str);
    return 0;
}