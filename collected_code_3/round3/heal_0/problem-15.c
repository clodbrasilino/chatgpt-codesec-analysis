#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** splitString(char* str) {
    int i, j = 0, k = 0;
    char** splitArr = (char**)malloc(sizeof(char*) * strlen(str));
    for(i = 0; i < strlen(str); i++) {
        splitArr[i] = (char*)malloc(sizeof(char) * strlen(str));
    }
    for(i = 0; i <= strlen(str); i++) {
        if(islower(str[i]) || str[i] == '\0') {
            splitArr[j][k] = '\0';
            j++;
            k = 0;
        } else {
            splitArr[j][k++] = str[i];
        }
    }
    return splitArr;
}

int main() {
    char str[] = "HelloWorld";
    char** splitArr = splitString(str);
    int i;
    for(i = 0; i < strlen(str); i++) {
        if(splitArr[i][0] == '\0') {
            break;
        }
        printf("%s\n", splitArr[i]);
        free(splitArr[i]);
    }
    free(splitArr);
    return 0;
}