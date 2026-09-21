#include <stdio.h>
#include <stddef.h>

void reverseString(char* str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void leftRotateString(char* str, size_t str_size, size_t n) {
    if (str == NULL || str_size == 0) {
        return;
    }

    size_t len = 0;
    while (len < str_size && str[len] != '\0') {
        len++;
    }

    if (len == 0 || n == 0 || n % len == 0) {
        return;
    }

    n = n % len;
    
    reverseString(str, 0, n - 1);
    reverseString(str, n, len - 1);
    reverseString(str, 0, len - 1);
}

int main(void) {
    char str[] = "HelloWorld";
    size_t rotations = 3;

    leftRotateString(str, sizeof(str), rotations);
    printf("%s\n", str);

    return 0;
}