#include <stdio.h>
#include <string.h>

void sortTuples(char tuples[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (strcmp(tuples[j], tuples[j + 1]) > 0) {
                /* Possible weaknesses found:
                 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
                 */
                char temp[2];
                /* Possible weaknesses found:
                 *  Cannot determine that 'temp[0]' is initialized [premium-bughuntingUninit]
                 *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
                 */
                strcpy(temp, tuples[j]);
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
                 *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                strcpy(tuples[j], tuples[j + 1]);
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
                 *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                strcpy(tuples[j + 1], temp);
            }
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *  (near initialization for 'tuples[2]')
     *  (near initialization for 'tuples[1]')
     *  excess elements in 'char' array initializer
     *  (near initialization for 'tuples[0]')
     */
    char tuples[][2] = {{"b", "2"}, {"a", "1"}, {"c", "3"}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for (int i = 0; i < size; i++) {
        printf("(%s, %s) ", tuples[i][0], tuples[i][1]);
    }

    return 0;
}