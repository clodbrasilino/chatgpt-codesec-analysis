#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(char *str) {
    char *new_str = str;
    for (int i = 0, len = strlen(str); i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            memmove(&str[i + 1], &str[i], len - i);
            str[i] = '_';
            str[i + 1] = tolower((unsigned char)str[i + 1]);
            len++;
            new_str = &str[i + 1];
            i++;
        }
    }
    return new_str - 1;
}

int main() {
    char str[256];
    printf("Enter a camel case string: ");
    scanf("%255s", str);
    camel_to_snake(str);
    printf("Snake case: %s\n", str);
    return 0;
}