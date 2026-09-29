#include <stdio.h>
#include <string.h>

#define ASCII_SIZE 256

char getMostCommonChar(char* str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0; 
    char result; 

    for (int i = 0; i < len; i++) {
        count[(int)str[i]]++;
        if (max < count[(int)str[i]]) {
            max = count[(int)str[i]];
            result = str[i];
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'result' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return result;
}

int main() {
    char str[] = "samplestring";
    printf("Most common character in '%s' is '%c'\n", str, getMostCommonChar(str));
    return 0;
}