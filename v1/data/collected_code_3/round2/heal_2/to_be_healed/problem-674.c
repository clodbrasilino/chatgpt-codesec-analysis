#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {
    char* result = (char*) malloc(strlen(str) + 1);
    char* word = strtok(str, " ");
    
    if(word!=NULL){
        strcpy(result, word);
        strcat(result, " ");
        
        while (word != NULL) {
            word = strtok(NULL, " ");
            if (word != NULL && !strstr(result, word)) {
                strcat(result, word);
                strcat(result, " ");
            }
        }
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