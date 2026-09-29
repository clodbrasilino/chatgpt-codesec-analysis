#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char** splitAtLowercase(const char* str) {
    int i, j = 0, k = 0;
    char** result = malloc(sizeof(char*) * strlen(str));
    for(i = 0; i < strlen(str); i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[j] = malloc(sizeof(char) * strlen(str));
        if(islower(str[i])) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*result_52 + _14 + (sizetype)k' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j][k] = '\0';
            j++;
            k = 0;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*result_52 + _22 + (sizetype)k' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j][k] = str[i];
            k++;
        }
    }
    result[j][k] = '\0';
    result[j+1] = NULL;
    return result;
}

int main() {
    char* str = "HelloWORLDHowAREYou";
    char** result = splitAtLowercase(str);
    int i = 0;
    while(result[i] != NULL) {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
    return 0;
}