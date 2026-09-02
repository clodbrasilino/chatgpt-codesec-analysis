#include <stdio.h>
#include <string.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int i;
    int max = -1;
    char result;

    while (*str) {
        count[(unsigned char)*str]++;
        if (max < count[(unsigned char)*str]) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    return result;
}

int main() {
    const char *testStr = "example string with text";
    char maxChar = findMaxOccurringChar(testStr);
    printf("Max occurring character: %c\n", maxChar);
    return 0;
}