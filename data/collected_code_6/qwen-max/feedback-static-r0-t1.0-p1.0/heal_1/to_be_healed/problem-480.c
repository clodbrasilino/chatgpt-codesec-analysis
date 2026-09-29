#include <stdio.h>
#include <string.h>
#include <limits.h>

/* Possible weaknesses found:
 *  'findMaxOccurringChar' declared here
 */
int findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = -1, result;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; str[i]; i++) {
        count[(unsigned char)str[i]]++;
        if (max < count[(unsigned char)str[i]]) {
            max = count[(unsigned char)str[i]];
            result = (unsigned char)str[i];
        }
    }
    /* Possible weaknesses found:
     *  Uninitialized variable: result
     *  Uninitialized variable: result [uninitvar]
     */
    return result;
}

int main() {
    const char *input = "test string";
    /* Possible weaknesses found:
     *  did you mean 'findMaxOccurringChar'?
     *  call to undeclared function 'findMaxOccuringChar'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'findMaxOccuringChar'; did you mean 'findMaxOccurringChar'? [-Wimplicit-function-declaration]
     */
    int maxChar = findMaxOccuringChar(input);
    printf("The maximum occurring character is: %c\n", maxChar);
    return 0;
}