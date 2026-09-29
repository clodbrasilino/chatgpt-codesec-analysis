#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_lowercase_substrings(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (isupper((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return str;
}

int main() {
    char input[] = "HeLlO wOrLd!";
    printf("Original: %s\n", input);
    char *result = remove_lowercase_substrings(input);
    printf("Modified: %s\n", result);
    return 0;
}