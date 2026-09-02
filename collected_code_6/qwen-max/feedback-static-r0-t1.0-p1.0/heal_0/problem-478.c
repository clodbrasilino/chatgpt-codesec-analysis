#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_lowercase(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (!islower((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char input[] = "HeLlO wOrLd";
    remove_lowercase(input);
    printf("%s\n", input);
    return 0;
}