#include <stdio.h>
#include <string.h>
#include <limits.h>

int findMostCommonChar(const char *str, char *mostCommon) {
    int count[256] = {0};
    int maxCount = 0;
    for (int i = 0; str[i]; ++i) {
        count[(unsigned char)str[i]]++;
        if (count[(unsigned char)str[i]] > maxCount) {
            maxCount = count[(unsigned char)str[i]];
            *mostCommon = str[i];
        }
    }
    return maxCount;
}

int main() {
    const char *input = "example string with some characters";
    char mostCommon;
    int frequency = findMostCommonChar(input, &mostCommon);
    printf("The most common character is '%c' which appears %d times.\n", mostCommon, frequency);
    return 0;
}