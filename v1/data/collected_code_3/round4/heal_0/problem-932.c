#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

void removeDuplicates(char* str) {
    char word[MAX_SIZE][MAX_SIZE], temp[MAX_SIZE];
    int i, j, k, stringCount = 0, wordCount;

    j = 0;
    for(i=0; str[i]!='\0'; i++) {
        if(str[i] != ' ') {
            temp[j] = str[i];
            j++;
        } else {
            temp[j] = '\0';
            strcpy(word[stringCount], temp);
            stringCount++;
            j = 0;
        }
    }

    temp[j] = '\0';
    strcpy(word[stringCount], temp);

    wordCount = stringCount + 1;

    for(i=0; i<wordCount; i++) {
        for(j=i+1; j<wordCount; j++) {
            if(strcmp(word[i], word[j]) == 0) {
                for(k=j; k<wordCount; k++) {
                    strcpy(word[k], word[k + 1]);
                }
                wordCount--;
                j--;
            }
        }
    }

    for(i=0; i<wordCount; i++) {
        printf("%s ", word[i]);
    }
}

int main() {
    char str[MAX_SIZE];

    printf("Enter any string: ");
    fgets(str, MAX_SIZE, stdin);

    str[strlen(str) - 1] = '\0';

    printf("String after removing duplicates: ");
    removeDuplicates(str);

    return 0;
}