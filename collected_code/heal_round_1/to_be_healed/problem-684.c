#include <stdio.h>

int countOccurrences(char *str, char c) {
    int count = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "ababab";
    char c = 'a';
    
    int occurrences = countOccurrences(str, c);
    printf("Number of occurrences of '%c' in the string: %d\n", c, occurrences);
    
    return 0;
}