#include <stdio.h>

void replaceOccurrences(char *str, int n) {
    int count = 0;
    char *ptr = str;

    while (ptr != NULL && *ptr != '\0' && count < n) {
        if (*ptr == ' ' || *ptr == ',' || *ptr == '.') {
            *ptr = ':';
            count++;
        }
        ptr++;
    }
}

int main() {
    char str[] = "Hello, world. This is a test.";

    replaceOccurrences(str, 3);

    printf("%s\n", str);

    return 0;
}