#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    char *read = str;
    char *write = str;
    while (*read) {
        if ((*read - '0') % 2 == 0 || *read < '0' || *read > '9') {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}

int main() {
    char str[] = "1234567890";
    remove_odd_chars(str);
    printf("%s\n", str);
    return 0;
}