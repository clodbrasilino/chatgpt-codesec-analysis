#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        if(strings[i] == NULL) continue;
        int len = strlen(strings[i]);
        char* str = malloc(len + 1);

        if(str == NULL) continue;
        strncpy(str, strings[i], len);
        
        for(int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }

        str[len] = '\0';
        strncpy(strings[i], str, len);
        strings[i][len] = '\0';
        free(str);
    }
}

int main(void) {
    const int numStrings = 3;
    char* strings[numStrings];
    strings[0] = strdup("hello");
    strings[1] = strdup("world");
    strings[2] = strdup("example");

    reverseStrings(strings, numStrings);
    
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    return 0;
}