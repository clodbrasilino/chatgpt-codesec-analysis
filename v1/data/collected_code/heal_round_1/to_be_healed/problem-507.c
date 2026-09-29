#include <stdio.h>
#include <string.h>

void removeSpecificWords(char list[][100], int size, char word[]) {
    int i, j, k;
    
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'word[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (strcmp(list[i], word) == 0) {
            for (j = i; j < size - 1; j++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'list[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
                 */
                strcpy(list[j], list[j + 1]);
            }
            /* Possible weaknesses found:
             *  Cannot determine that 'list[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused). Risk is low because the source is a constant character.
             */
            strcpy(list[size - 1], "");
            size--;
            i--;
        }
    }
}

int main() {
    char words[][100] = {"apple", "banana", "orange", "grape", "apple"};
    int size = sizeof(words) / sizeof(words[0]);
    
    removeSpecificWords(words, size, "apple");
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", words[i]);
    }
    
    return 0;
}