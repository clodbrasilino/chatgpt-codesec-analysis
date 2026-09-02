#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMostCommonChar(const char *str) {
    int count[256] = {0};
    int max = 0;
    char result;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (*str) {
        count[(unsigned char)*str]++;
        if (count[(unsigned char)*str] > max) {
            max = count[(unsigned char)*str];
            result = *str;
        }
        str++;
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: result
     *  Uninitialized variable: result [uninitvar]
     */
    return result;
}

int main() {
    const char *input = "example string with some characters";
    char mostCommon = findMostCommonChar(input);
    printf("The most common character is: '%c'\n", mostCommon);
    return 0;
}