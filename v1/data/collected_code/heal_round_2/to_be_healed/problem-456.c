#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int len = strlen(strings[i]);
        char* str = malloc(len + 1);
        
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
         */
        strcpy(str, strings[i]);

        for(int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
        
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
         */
        strcpy(strings[i], str);
        free(str);
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char strings[3][10] = {"hello", "world", "example"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    reverseStrings((char**)strings, numStrings);
    
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}