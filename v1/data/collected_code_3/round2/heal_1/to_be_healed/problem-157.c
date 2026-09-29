#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* runLengthEncoding(char* str) {
    int n = strlen(str);
    char* result = (char*)malloc(sizeof(char) * n * 2 + 1);
    int count = 1;
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == str[i + 1]) {
            count++;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j++] = count + '0';
            result[j++] = str[i];
            count = 1;
        }
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "aaabbbccc";
    char* encodedStr = runLengthEncoding(str);
    printf("%s\n", encodedStr);
    free(encodedStr);
    return 0;
}