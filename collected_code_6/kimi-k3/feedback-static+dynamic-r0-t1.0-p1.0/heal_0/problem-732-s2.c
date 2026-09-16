#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    replace_chars(buffer);
    printf("%s\n", buffer);
    return 0;
}