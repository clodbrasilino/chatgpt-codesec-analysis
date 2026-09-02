#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = -1;
    char result;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (*str) {
        count[(unsigned char)*str]++;
        if (max < count[(unsigned char)*str]) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: result [uninitvar]
     *  Uninitialized variable: result
     */
    return result;
}

int main() {
    const char *input = "example string with some characters";
    char maxChar = findMaxOccurringChar(input);
    printf("The maximum occurring character is: %c\n", maxChar);
    return 0;
}