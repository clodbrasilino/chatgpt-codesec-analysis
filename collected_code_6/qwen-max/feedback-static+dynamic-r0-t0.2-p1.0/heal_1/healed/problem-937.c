#include <stdio.h>
#include <string.h>

char findMostCommonChar(const char *str) {
    int count[256] = {0};
    int max = 0;
    char result = '\0';

    while (*str) {
        count[(unsigned char)*str]++;
        if (count[(unsigned char)*str] > max) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    return result;
}

int main() {
    const char *input = "example string with some characters";
    char mostCommon = findMostCommonChar(input);
    printf("The most common character is: '%c'\n", mostCommon);
    return 0;
}