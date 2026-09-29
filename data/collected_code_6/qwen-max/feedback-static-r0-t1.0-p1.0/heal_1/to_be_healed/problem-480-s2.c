#include <stdio.h>
#include <string.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    int i;
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
     *  Uninitialized variable: result
     *  Uninitialized variable: result [uninitvar]
     */
    return result;
}

int main() {
    const char *testStr = "example string with text";
    char maxChar = findMaxOccurringChar(testStr);
    printf("Max occurring character: %c\n", maxChar);
    return 0;
}