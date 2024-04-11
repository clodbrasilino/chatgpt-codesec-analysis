#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {

    if(!str) return NULL;
    
    char* result = (char*)malloc(strlen(str) + 1);
    if(!result) return NULL;

    char* word = (char*)malloc(strlen(str) + 1);
    if(!word) {
        free(result);
        return NULL;
    }

    int i = 0, j = 0, wordLength = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            word[wordLength++] = str[i];
        } else {
            if (wordLength != k) {
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
        result[j+wordLength] = '\0';
    } else {
        result[j] = '\0';
    }

    free(word);
    return result;
}

int main() {
    char str[] = "Hello world this is a test string";
    int k = 4;
    char* result = removeWords(str, k);
    if(result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}