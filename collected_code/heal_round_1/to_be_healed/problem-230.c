#include <stdio.h>

void replaceSpaces(char *str, char ch) {
    int i;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    char ch;
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
    printf("Enter the character to replace spaces with: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'ch' is initialized [premium-bughuntingUninit]
     */
    scanf("%c", &ch);
    replaceSpaces(str, ch);
    printf("Modified string: %s", str);
    return 0;
}