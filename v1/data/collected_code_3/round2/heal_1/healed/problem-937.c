#include <stdio.h>
#include <string.h>

#define ASCII_SIZE 256

char getMostCommonChar(char* str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0;
    char result = 0;

    for (int i = 0; i < len; i++) {
        count[(int)(str[i])]++;
        if (max < count[(int)(str[i])]) {
            max = count[(int)(str[i])];
            result = str[i];
        }
    }
    return result;
}

int main() {
    char str[] = "sample string";
    printf("Most common character is %c\n", getMostCommonChar(str));
    return 0;
}