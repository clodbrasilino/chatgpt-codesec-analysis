#include <stdio.h>

int countLowerCase(char* str) {
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            count++;
        }
        i++;
    }

    return count;
}

int main() {
    char* text = "Hello, World!";
    int result = countLowerCase(text);

    printf("Number of lower case letters: %d\n", result);

    return 0;
}