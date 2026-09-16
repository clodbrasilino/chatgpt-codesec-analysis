#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* remove_lower_substrings(char *str) {
    char *src = str;
    char *dest = str;
    while (*src) {
        if (islower(*src)) {
            while (*src && islower(*src)) {
                src++;
            }
            continue;
        }
        *dest++ = *src++;
    }
    *dest = '\0';
    return str;
}

int main() {
    char input[] = "ThIs Is a TeSt sTrinG";
    printf("Original: %s\n", input);
    remove_lower_substrings(input);
    printf("Modified: %s\n", input);
    return 0;
}