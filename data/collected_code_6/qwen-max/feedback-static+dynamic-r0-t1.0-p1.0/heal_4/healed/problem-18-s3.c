#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, size_t str1_len, const char *str2) {
    char *src, *dst;
    for (src = dst = str1; src - str1 < str1_len && *src != '\0'; ++src) {
        if (strchr(str2, *src) == NULL) {
            *dst++ = *src;
        }
    }
    *dst = '\0';
}

int main() {
    char str1[100] = "Hello, World!";
    const char *str2 = ",!";
    size_t str1_len = strlen(str1);

    remove_chars(str1, str1_len, str2);
    printf("%s\n", str1);

    return 0;
}