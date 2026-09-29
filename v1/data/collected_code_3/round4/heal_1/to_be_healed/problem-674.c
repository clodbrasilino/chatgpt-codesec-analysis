#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {
    char* result = malloc(strlen(str) + 1);
    char* word = strtok(str, " ");
    while (word != NULL) {
        /* Possible weaknesses found:
         *  use of possibly-NULL 'result' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        if (!strstr(result, word)) {
            strcat(result, " ");
            strcat(result, word);
        }
        word = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "This is a test. This is only a test.";
    char* result = removeDuplicates(str);
    /* Possible weaknesses found:
     *  use of possibly-NULL 'result' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     */
    printf("%s\n", result);
    free(result);
    return 0;
}