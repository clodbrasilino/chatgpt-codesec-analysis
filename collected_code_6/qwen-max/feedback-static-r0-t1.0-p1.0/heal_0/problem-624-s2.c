#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_upper(char *str) {
    for (; *str; ++str) {
        *str = toupper((unsigned char)*str);
    }
}

int main() {
    char str[] = "Hello, World!";
    to_upper(str);
    printf("%s\n", str);
    return 0;
}