#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_whitespaces(char *str) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        if (!isspace((unsigned char)*src)) {
            *dst++ = *src;
        }
    }
    *dst = '\0';
}

int main() {
    char str[] = " Remove  whitespaces   from this  string. ";
    printf("Original string: '%s'\n", str);
    remove_whitespaces(str);
    printf("String after removing whitespaces: '%s'\n", str);
    return 0;
}