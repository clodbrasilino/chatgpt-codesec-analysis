#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void leftRotateString(char *str, size_t rotations) {
    size_t len = 0;

    if (str == NULL) {
        return;
    }

    while (str[len] != '\0') {
        len++;
    }

    if (len <= 1 || rotations == 0 || rotations % len == 0) {
        return;
    }

    rotations = rotations % len;

    reverseString(str, 0, rotations - 1);
    reverseString(str, rotations, len - 1);
    reverseString(str, 0, len - 1);
}

int main(void) {
    char str[] = "Hello, World!";
    size_t rotations = 7;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}