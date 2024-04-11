#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* removeSpecialCharacters(char* str) {
    int i = 0, j = 0;
    char *output = malloc(strlen(str) + 1);
    if (!output) {
        return NULL;
    }
    
    while(str[i]) {
        if(isalnum((unsigned char)str[i])) {
            output[j++] = str[i];
        }
        i++;
    }
    
    output[j] = '\0';
    return output;
}

int main() {
    char str[] = "Thi$ is @ te$ting Str!ng.";
    char *result = removeSpecialCharacters(str);
    if (!result) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("%s\n", result);
    free(result);
    return 0;
}