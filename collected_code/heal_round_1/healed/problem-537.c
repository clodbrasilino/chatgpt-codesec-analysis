#include <stdio.h>
#include <string.h>

char* findFirstRepeatedWord(char* str) {
    char *word, *temp;
    char* words[100] = {NULL};
    int i = 0;
    
    temp = (char*)malloc(strlen(str)+1);
    strcpy(temp,str);
    word = strtok(temp, " ");
    
    while (word != NULL) {
        for (int j = 0; j < i; j++) {
            if (strcmp(words[j], word) == 0) {
                free(temp);
                return word;
            }
        }
        
        words[i++] = word;
        word = strtok(NULL, " ");
    }
    
    free(temp);
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