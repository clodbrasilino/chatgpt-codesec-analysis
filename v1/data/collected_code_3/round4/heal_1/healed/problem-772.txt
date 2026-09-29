#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {
    char* result = (char*)malloc(strlen(str) + 1);
    if(result == NULL)
        return NULL;
    
    char* word = (char*)malloc(strlen(str) + 1);
    if(word == NULL){
        free(result);
        return NULL;
    }

    int i = 0, j = 0, wc = 0, rc = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ')
            word[wc++] = str[i];
        else {
            if (wc != k) {
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
        result[rc+wc] = '\0';
    } else {
        result[rc] = '\0';
    }

    free(word);
    return result;
}

int main() {
    char str[] = "This is a test string";
    int k = 2;
    char* result = removeWords(str, k);
    if(result != NULL){
        printf("%s\n", result);
        free(result);
    }
    return 0;
}