#include <stdio.h>
#include <string.h>

char* findFirstRepeatedWord(char* str) {
    char* word;
    char* words[100];
    int i = 0;
    
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