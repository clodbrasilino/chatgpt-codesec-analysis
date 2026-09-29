#include <stdio.h>

int countOccurrence(char str[], char c) {
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
    char str[] = "Hello, World!";
    char c = 'l';
    
    int occurrence = countOccurrence(str, c);
    printf("Occurrence of '%c' in '%s' is %d\n", c, str, occurrence);
    
    return 0;
}