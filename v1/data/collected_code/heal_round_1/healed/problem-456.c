#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        int len = strlen(strings[i]);
        char* str = malloc(len + 1);
        
        strcpy(str, strings[i]);

        for(int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
        
        strcpy(strings[i], str);
        free(str);
    }
}

int main() {
    char strings[3][10] = {"hello", "world", "example"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    reverseStrings((char**)strings, numStrings);
    
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}