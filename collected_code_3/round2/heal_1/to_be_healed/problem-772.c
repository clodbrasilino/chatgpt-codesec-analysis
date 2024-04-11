#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {
    char* result = (char*)malloc(strlen(str) + 1);
    char* word = (char*)malloc(strlen(str) + 1);
    int i = 0, j = 0, wordLength = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            word[wordLength++] = str[i];
        } else {
            if (wordLength != k) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                word[wordLength] = '\0';
                strcpy(result + j, word);
                j += wordLength;
                result[j++] = ' ';
            }
            wordLength = 0;
        }
        i++;
    }

    if (wordLength != k) {
        word[wordLength] = '\0';
        strcpy(result + j, word);
    } else {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[j] = '\0';
    }

    free(word);
    return result;
}

int main() {
    char str[] = "Hello world this is a test string";
    int k = 4;
    char* result = removeWords(str, k);
    printf("%s\n", result);
    free(result);
    return 0;
}