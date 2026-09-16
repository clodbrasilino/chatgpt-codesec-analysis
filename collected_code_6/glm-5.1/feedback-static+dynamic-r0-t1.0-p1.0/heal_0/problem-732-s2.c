#include <stdio.h>
#include <stdlib.h>

void replace_chars(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
        }
        str++;
    }
}

int main(void) {
    char input[] = "Hello, world. This is a test.";
    printf("Original: %s\n", input);
    replace_chars(input);
    printf("Modified: %s\n", input);
    return 0;
}