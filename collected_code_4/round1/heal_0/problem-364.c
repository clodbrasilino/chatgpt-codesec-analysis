#include <stdio.h>
#include <string.h>

int minFlips(char *str, int len) {
    int flipCount = 0;
    char expectedChar = '0';

    for (int i = 0; i < len; i++) {
        if (str[i] != expectedChar)
            flipCount++;

        expectedChar = (expectedChar == '0') ? '1' : '0';
    }

    return flipCount;
}

int main() {
    char str[] = "1010101";
    int len = strlen(str);
    printf("%d\n", minFlips(str, len));
    return 0;
}