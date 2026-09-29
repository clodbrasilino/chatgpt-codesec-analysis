#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void incrementNumericValues(char *str, int k) {
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {
            int num = str[i] - '0';
            num = (num + k) % 10;
            str[i] = num + '0';
        }
    }
}

int main() {
    char str[] = "abc123";
    int k = 3;
    incrementNumericValues(str, k);
    printf("%s\n", str);
    return 0;
}