#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** splitString(char* str) {
    size_t len = strlen(str);
    int i, j = 0, k = 0;
    char** splitArr = (char**)calloc(len + 1, sizeof(char*));

    if (splitArr == NULL){
      return NULL;
    }
    for(i = 0; i < len; i++) {
        splitArr[i] = (char*)calloc(len + 1, sizeof(char));
        if(splitArr[i] == NULL) {
          for(; i >= 0; i--)
            free(splitArr[i]);
          free(splitArr);
          return NULL;
        }
    }
    for(i = 0; i <= len; i++) {
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

    if(splitArr == NULL){
      return 1;
    }
    int i;
    for(i = 0; i < strlen(str) && splitArr[i]; i++) {
        if(splitArr[i][0] == '\0') {
            break;
        }
        printf("%s\n", splitArr[i]);
        free(splitArr[i]);
    }
    free(splitArr);
    return 0;
}