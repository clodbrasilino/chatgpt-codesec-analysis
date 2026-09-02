#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMostCommonChar(const char *str) {
    int count[256] = {0};
    int max = 0;
    char result = '\0';

    if (str == NULL || *str == '\0') {
        return result;
    }

    do {
        unsigned char ch = (unsigned char)*str;
        count[ch]++;
        if (count[ch] > max) {
            max = count[ch];
            result = *str;
        }
        str++;
    } while (*str);

    return result;
}

int main() {
    const char *input = "example string with some characters";
    char mostCommon = findMostCommonChar(input);
    printf("The most common character is: '%c'\n", mostCommon);
    return 0;
}