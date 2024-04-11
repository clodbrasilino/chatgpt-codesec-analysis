#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** splitString(char* str) {
    int i, j = 0, k = 0;
    char** splitArr = (char**)malloc(sizeof(char*) * strlen(str));
    for(i = 0; i < strlen(str); i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'splitArr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        splitArr[i] = (char*)malloc(sizeof(char) * strlen(str));
    }
    for(i = 0; i <= strlen(str); i++) {
        if(islower(str[i]) || str[i] == '\0') {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*splitArr_50 + _19 + (sizetype)k' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  use of uninitialized value '*splitArr_50 + _19' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             *  dereference of possibly-NULL 'splitArr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            splitArr[j][k] = '\0';
            j++;
            k = 0;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*splitArr_50 + _27 + (sizetype)k' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  use of uninitialized value '*splitArr_50 + _27' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             *  dereference of possibly-NULL 'splitArr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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
        /* Possible weaknesses found:
         *  use of uninitialized value '**_3' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  use of uninitialized value '*splitArr_21 + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL '*splitArr_21 + _2' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  dereference of possibly-NULL 'splitArr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        if(splitArr[i][0] == '\0') {
            break;
        }
        printf("%s\n", splitArr[i]);
        free(splitArr[i]);
    }
    free(splitArr);
    return 0;
}