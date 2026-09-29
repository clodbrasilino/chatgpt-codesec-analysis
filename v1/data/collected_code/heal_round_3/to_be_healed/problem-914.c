#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isMadeOfAlternatingCharacters(const char *str) {
    int i = 0;
  
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);

    if (length < 1) {
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
    char testString1[] = "AB";
    char testString2[] = "AA";

    printf("%d\n", isMadeOfAlternatingCharacters(testString1));
    printf("%d\n", isMadeOfAlternatingCharacters(testString2));

    return 0;
}