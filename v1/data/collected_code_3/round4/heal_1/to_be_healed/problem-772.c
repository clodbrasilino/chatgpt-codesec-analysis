#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {
    char* result = (char*)malloc(strlen(str) + 1);
    char* word = (char*)malloc(strlen(str) + 1);
    int i = 0, j = 0, wc = 0, rc = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            word[wc++] = str[i];
        } else {
            if (wc != k) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                word[wc] = '\0';
                strcpy(&result[rc], word);
                rc += wc;
                result[rc++] = ' ';
            }
            wc = 0;
        }
        i++;
    }

    if (wc != k) {
        word[wc] = '\0';
        strcpy(&result[rc], word);
    } else {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[rc] = '\0';
    }

    free(word);
    return result;
}

int main() {
    char str[] = "This is a test string";
    int k = 2;
    char* result = removeWords(str, k);
    printf("%s\n", result);
    free(result);
    return 0;
}