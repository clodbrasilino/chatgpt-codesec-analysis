#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        if(strings[i] == NULL) continue;
        size_t len = strnlen(strings[i], 1000);

        if(len <= 0) continue;
        char* str = (char*)malloc(sizeof(char) * (len + 1));

        if(str == NULL) continue;
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(str, strings[i], len+1);

        for(int j = 0; j < len/2; j++) {
            char temp = str[j];
            /* Possible weaknesses found:
             *  heap-based buffer over-read [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            str[j] = str[len-j-1];
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            str[len-j-1] = temp;
        } 

        str[len] = '\0';
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(strings[i], str, len+1);

        free(str);
    }
}

int main(void) {
    const int numStrings = 3;
    char* strings[numStrings];
    strings[0] = strdup("hello");
    strings[1] = strdup("world");
    strings[2] = strdup("example");

    if(strings[0] && strings[1] && strings[2]){
        reverseStrings(strings, numStrings);

        for (int i = 0; i < numStrings; i++) {
            printf("%s\n", strings[i]);
            free(strings[i]);
        }
    }

    return 0;
}