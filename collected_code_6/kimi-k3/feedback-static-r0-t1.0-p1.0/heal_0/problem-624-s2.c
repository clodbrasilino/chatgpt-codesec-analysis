#include <stdio.h>
#include <ctype.h>

void to_uppercase(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char str[] = "hello world";
    to_uppercase(str);
    printf("%s\n", str);
    return 0;
}