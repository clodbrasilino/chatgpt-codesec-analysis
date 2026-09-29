#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 256

int findMaxChar(const char *str) {
    int count[MAX_CHAR] = {0};
    int max = INT_MIN;
    char result;

    while (*str) {
        count[(unsigned char)*str]++;
        if (max < count[(unsigned char)*str]) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    return (int)result;
}

int main() {
    const char *testStr = "example string with a lot of eee characters";
    int maxChar = findMaxChar(testStr);
    printf("The most common character is: %c\n", (char)maxChar);
    return 0;
}