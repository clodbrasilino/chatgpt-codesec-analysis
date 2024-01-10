#include <stdio.h>
#include <string.h>

void mergeDictionaries(char dictionary1[][100], char dictionary2[][100], int size1, int size2) {
    int i, j, flag;

    // Merging dictionaries
    for (i = 0; i < size2; i++) {
        flag = 0;
        for (j = 0; j < size1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'dictionary1[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (strcmp(dictionary1[j], dictionary2[i]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
             *  Cannot determine that 'dictionary1[size1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            strcpy(dictionary1[size1], dictionary2[i]);
            size1++;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char dictionary1[100][100], dictionary2[100][100];
    int size1, size2, i;

    // Read the size of first dictionary
    printf("Enter the number of elements in the first dictionary: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size1);

    // Read elements of first dictionary
    printf("Enter the elements of the first dictionary:\n");
    for (i = 0; i < size1; i++) {
        /* Possible weaknesses found:
         *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
         *  Cannot determine that 'dictionary1[i]' is initialized [premium-bughuntingUninit]
         */
        scanf("%s", dictionary1[i]);
    }

    // Read the size of second dictionary
    printf("Enter the number of elements in the second dictionary: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size2' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size2);

    // Read elements of second dictionary
    printf("Enter the elements of the second dictionary:\n");
    for (i = 0; i < size2; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary2[i]' is initialized [premium-bughuntingUninit]
         *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
         */
        scanf("%s", dictionary2[i]);
    }

    // Call the merge function
    mergeDictionaries(dictionary1, dictionary2, size1, size2);

    // Print the merged dictionary
    printf("\nMerged Dictionary:\n");
    for (i = 0; i < size1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary1[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%s\n", dictionary1[i]);
    }

    return 0;
}