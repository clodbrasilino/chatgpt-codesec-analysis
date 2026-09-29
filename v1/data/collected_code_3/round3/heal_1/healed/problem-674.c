#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

struct Word {
    char str[MAX_WORD_LENGTH];
    struct Word* next;
};

struct Word* createWord(char* str) {
    struct Word* newWord = (struct Word*) malloc(sizeof(struct Word));

    if (newWord == NULL) {
        return NULL;
    }

    strcpy(newWord->str, str);
    newWord->next = NULL;

    return newWord;
}

int contains(struct Word* root, char* str) {
    struct Word* temp = root;

    while(temp != NULL) {
        if(strcmp(temp->str, str) == 0)
            return 1;
        temp = temp->next;
    }

    return 0;
}

void freeWords(struct Word* root) {
    while(root != NULL) {
        struct Word* temp = root;
        root = root->next;
        free(temp);
    }
}

void removeDuplicates(char* str) {
    struct Word* root = NULL;
    char* token = strtok(str, " ");

    while(token != NULL) {
        if(!contains(root, token)) {
            struct Word* newWord = createWord(token);

            if (newWord == NULL) {
              freeWords(root);
              return;
            }

            newWord->next = root;
            root = newWord;
            printf("%s ", token);
        }
        token = strtok(NULL, " ");
    }
  
    freeWords(root);
}

int main() {
    char str[MAX_WORDS * MAX_WORD_LENGTH];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    removeDuplicates(str);
    return 0;
}