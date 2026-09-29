#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(char *str) {
    int len = strlen(str);
    char *new_str = malloc(len * 2 + 1);
    if (!new_str) return NULL;
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0) new_str[j++] = '_';
            new_str[j++] = tolower((unsigned char)str[i]);
        } else {
            new_str[j++] = str[i];
        }
    }
    new_str[j] = '\0';
    return new_str;
}

int main() {
    char str[256];
    printf("Enter a camel case string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    char *snake_str = camel_to_snake(str);
    if (snake_str) {
        printf("Snake case: %s\n", snake_str);
        free(snake_str);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}