#include <stdio.h>

void leftRotateString(char* str, int n) {
    int len = strlen(str);
    int rotations = n % len;

    for (int i = 0; i < rotations; i++) {
        char firstChar = str[0];

        for (int j = 0; j < len - 1; j++) {
            str[j] = str[j + 1];
        }

        str[len - 1] = firstChar;
    }
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}