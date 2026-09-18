#include <stdio.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#define ASCII_SIZE 256

char getMaxOccurringChar(char* str) {
    int count[ASCII_SIZE] = {0};
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
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
    return result;
}

int main() {
    char str[] = "sample string";
    printf("Max occurring character is '%c'.\n", getMaxOccurringChar(str));
    return 0;
}