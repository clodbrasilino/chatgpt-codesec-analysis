#include <stdio.h>
#include <string.h>
#define ASCII_SIZE 256

void findMostCommon(char* str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0;
    char result = str[0];

    for (int i = 0; i < len; i++) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }

    printf("Most common character: %c, count: %d\n", result, max);
}

int main() {
    char str[] = "Hello, World!";
    findMostCommon(str);
    return 0;
}