#include <stdio.h>
#include <string.h>

void removeMultipleSpaces(char *str) {
    int i, j;
    int flag = 0;
    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; str[i]; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] == ' ' && str[i + 1] == ' ') {
            flag = 1;
        } else {
            if (flag == 1) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'j++' is initialized [premium-bughuntingUninit]
                 *  use of uninitialized value 'j' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
                 */
                str[j++] = ' ';
                flag = 0;
            }
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  use of uninitialized value 'j' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            str[j++] = str[i];
        }
    }
    /* Possible weaknesses found:
     *  use of uninitialized value 'j' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    removeMultipleSpaces(str);

    printf("String after removing multiple spaces: %s\n", str);

    return 0;
}