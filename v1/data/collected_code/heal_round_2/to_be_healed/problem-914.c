#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isMadeOfAlternatingCharacters(const char *str) {
    int i = 0;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);

    if (length != 2) {
        return false;
    }
    
    while (i < length - 1) {
        if (str[i] == str[i + 1]) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main() {
    char *testString1 = "AB";
    char *testString2 = "AA";

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("%d\n", isMadeOfAlternatingCharacters(testString1));
    printf("%d\n", isMadeOfAlternatingCharacters(testString2));

    return 0;
}