#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = 0;
    char result = '\0';

    while (*str) {
        count[(unsigned char)*str]++;
        if (max < count[(unsigned char)*str]) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    return max > 0 ? result : '\0';
}

int main() {
    const char *input = "test string";
    char maxChar = findMaxOccurringChar(input);
    if (maxChar) {
        printf("Max occurring character: %c\n", maxChar);
    } else {
        printf("No characters found.\n");
    }
    return 0;
}