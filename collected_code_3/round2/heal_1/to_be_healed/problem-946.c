#include <stdio.h>
#include <string.h>
#define ASCII_SIZE 256

void findMostCommon(char* str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0;
    char result;

    for (int i = 0; i < len; i++) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'result' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    printf("Most common character: %c, Count: %d\n", result, max);
}

int main() {
    char str[] = "Hello, World!";
    findMostCommon(str);
    return 0;
}