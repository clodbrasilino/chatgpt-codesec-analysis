#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void remove_multiple_spaces(char* str) {
    char* p = str;
    bool was_space = false;

    while (*str != '\0') {
        if (isspace(*str)) {
            if (!was_space) {
                *p++ = ' ';
                was_space = true;
            }
        } else {
            *p++ = *str;
            was_space = false;
        }
        str++;
    }
    *p = '\0';
}

int main() {
    char str[] = "Hello       world   !";
    printf("Original string: %s\n", str);
    remove_multiple_spaces(str);
    printf("Processed string: %s\n", str);
    return 0;
}