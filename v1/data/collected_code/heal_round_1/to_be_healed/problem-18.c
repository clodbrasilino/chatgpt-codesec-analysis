#include <stdio.h>

void removeChars(char *str1, char *str2) {
    int count = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str1[i] != '\0'; i++) {
        int flag = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'str2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        for (int j = 0; str2[j] != '\0'; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'str2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (str1[i] == str2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            str1[count++] = str1[i];
        }
    }
    str1[count] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[100], str2[100];
    printf("Enter the first string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", str1);
    printf("Enter the second string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str2[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", str2);

    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);

    return 0;
}