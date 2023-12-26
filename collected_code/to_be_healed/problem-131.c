#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

int isVowel(char ch) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
     */
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

void reverseVowels(char *str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int i = 0, j = strlen(str) - 1;
    while (i < j) {
        if (!isVowel(str[i])) {
            i++;
            continue;
        }
        if (!isVowel(str[j])) {
            j--;
            continue;
        }
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
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
    scanf("%[^\n]s", str);
    reverseVowels(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
