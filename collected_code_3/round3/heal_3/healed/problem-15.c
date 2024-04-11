#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** splitString(char* str) {
    size_t len = strlen(str);
    char** splitArr = (char**)calloc(len + 1, sizeof(char*));

    if (splitArr == NULL){
        return NULL;
    }

    for(size_t i = 0; i < len; i++) {
        splitArr[i] = (char*)calloc(len + 1, sizeof(char));
        if(splitArr[i] == NULL) {
            while(i > 0){
                free(splitArr[--i]);
            }
            free(splitArr);
            return NULL;
        }
    }

    for(size_t i = 0, j = 0, k = 0; str[i] != '\0'; i++) {
        if(islower(str[i])) {
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

    if(splitArr == NULL){
        return 1;
    }

    for(size_t i = 0; i < strlen(str); i++) {
        if(splitArr[i] == NULL || splitArr[i][0] == '\0') {
            break;
        }
        printf("%s\n", splitArr[i]);
        free(splitArr[i]);
        splitArr[i] = NULL;
    }
    free(splitArr);
    splitArr = NULL;
    return 0;
}