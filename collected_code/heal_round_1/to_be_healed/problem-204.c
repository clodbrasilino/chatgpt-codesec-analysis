#include <stdio.h>

int countOccurrence(char str[], char ch) {
    int count = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] == ch) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello, World!";
    char ch = 'l';
    int occurrence = countOccurrence(str, ch);
    printf("Occurrence of %c in string: %d", ch, occurrence);

    return 0;
}