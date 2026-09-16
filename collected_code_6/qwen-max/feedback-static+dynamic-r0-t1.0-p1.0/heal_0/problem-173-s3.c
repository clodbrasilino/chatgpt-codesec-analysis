#include <stdio.h>
#include <ctype.h>
#include <string.h>

void sanitize_string(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
        if (isalnum((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char input[] = "He!llo, W&orld? 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}