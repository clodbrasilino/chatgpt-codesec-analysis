#include <stdio.h>
#include <string.h>

void reverse(char str[]) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void reverseStrings(char *str[], int len) {
    for (int i = 0; i < len; i++) {
        reverse(str[i]);
    }
}

int main() {
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[] = "C Programming";
    char *str[] = {str1, str2, str3};
    int len = sizeof(str) / sizeof(str[0]);

    reverseStrings(str, len);

    for (int i = 0; i < len; i++) {
        printf("%s\n", str[i]);
    }

    return 0;
}