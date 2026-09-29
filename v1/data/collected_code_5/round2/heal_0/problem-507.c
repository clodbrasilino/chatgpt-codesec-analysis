#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 100
#define MAX_WORD_SIZE 50

void removeWord(char list[][MAX_WORD_SIZE], int *size, char *word) {
    int i, j;
    for(i = 0; i < *size; i++) {
        if(strcmp(list[i], word) == 0) {
            for(j = i; j < (*size) - 1; j++) {
                strcpy(list[j], list[j + 1]);
            }
            (*size)--;
            i--;
        }
    }
}

int main() {
    char list[MAX_LIST_SIZE][MAX_WORD_SIZE];
    int size, i;
    char word[MAX_WORD_SIZE];

    printf("Enter the size of the list: ");
    scanf("%d", &size);

    if (size < 0 || size > MAX_LIST_SIZE) {
        printf("Invalid size\n");
        return 1;
    }

    printf("Enter the words in the list:\n");
    for(i = 0; i < size; i++) {
        scanf("%s", list[i]);
    }

    printf("Enter the word to remove: ");
    scanf("%s", word);

    removeWord(list, &size, word);

    printf("The list after removing the word:\n");
    for(i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}