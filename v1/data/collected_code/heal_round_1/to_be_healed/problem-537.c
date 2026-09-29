#include <stdio.h>
#include <string.h>

char* findFirstRepeatedWord(char* str) {
    char* word;
    /* Possible weaknesses found:
     *  Cannot determine that 'words[100]' is initialized [premium-bughuntingUninit]
     */
    char* words[100];
    int i = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    word = strtok(str, " ");
    
    while (word != NULL) {
        for (int j = 0; j < i; j++) {
            if (strcmp(words[j], word) == 0) {
                return word;
            }
        }
        
        words[i++] = word;
        word = strtok(NULL, " ");
    }
    
    return NULL;
}

int main() {
    char str[] = "This is a sample string with repeated words";
    char* repeatedWord = findFirstRepeatedWord(str);
    
    if (repeatedWord != NULL) {
        printf("First repeated word: %s\n", repeatedWord);
    } else {
        printf("No repeated word found\n");
    }
    
    return 0;
}