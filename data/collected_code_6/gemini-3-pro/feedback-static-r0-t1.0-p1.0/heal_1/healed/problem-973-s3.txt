#include <stdio.h>
#include <stdlib.h>

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
    if (str == NULL) {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0 || rotations == 0 || rotations % len == 0) {
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