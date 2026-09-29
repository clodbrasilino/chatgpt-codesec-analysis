#include <stdio.h>
#include <string.h>

void reverseSubString(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void leftRotateString(char *str, size_t d) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);

    if (len == 0 || d == 0) {
        return;
    }

    d = d % len;
    if (d == 0) {
        return;
    }

    reverseSubString(str, 0, d - 1);
    reverseSubString(str, d, len - 1);
    reverseSubString(str, 0, len - 1);
}

int main(void) {
    char str[] = "HelloWorld";
    size_t d = 3;

    leftRotateString(str, d);
    printf("%s\n", str);

    return 0;
}