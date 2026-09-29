#include <stdio.h>
#include <string.h>
#include <limits.h>

int findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = -1, result;
    for (int i = 0; str[i]; i++) {
        count[(unsigned char)str[i]]++;
        if (max < count[(unsigned char)str[i]]) {
            max = count[(unsigned char)str[i]];
            result = (unsigned char)str[i];
        }
    }
    return result;
}

int main() {
    const char *input = "test string";
    int maxChar = findMaxOccuringChar(input);
    printf("The maximum occurring character is: %c\n", maxChar);
    return 0;
}