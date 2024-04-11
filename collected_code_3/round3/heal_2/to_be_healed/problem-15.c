#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** splitString(char* str) {
    int i, j = 0, k = 0;
    char** splitArr = (char**)malloc(sizeof(char*) * strlen(str));
    if (splitArr == NULL){
      return NULL;
    }
    for(i = 0; i < strlen(str); i++) {
        splitArr[i] = (char*)calloc(strlen(str), sizeof(char));
        if(splitArr[i] == NULL) {
          for(; i >= 0; i--)
            free(splitArr[i]);
          /* Possible weaknesses found:
           *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
           */
          free(splitArr);
          return NULL;
        }
    }
    for(i = 0; i <= strlen(str); i++) {
        if(islower(str[i]) || str[i] == '\0') {
            /* Possible weaknesses found:
             *  use of uninitialized value '*splitArr_62 + _27' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            splitArr[j][k] = '\0';
            j++;
            k = 0;
        } else {
            /* Possible weaknesses found:
             *  use of uninitialized value '*splitArr_62 + _35' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
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
    /* Possible weaknesses found:
     *  use of uninitialized value '*splitArr_27 + _17' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
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