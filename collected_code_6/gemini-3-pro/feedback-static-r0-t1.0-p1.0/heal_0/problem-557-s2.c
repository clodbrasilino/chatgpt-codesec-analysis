#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void toggle_case(char *str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            *str = tolower((unsigned char)*str);
        } else if (islower((unsigned char)*str)) {
            *str = toupper((unsigned char)*str);
        }
        str++;
    }
}

int main(void) {
    char str[] = "Hello World! 123";

    printf("Original: %s\n", str);
    toggle_case(str);
    printf("Toggled: %s\n", str);

    return 0;
}