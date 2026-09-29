#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_WORD_LIST_SIZE 100

void remove_specific_word(char* word_list[], char* remove_word, int size) {
    for(int i = 0; i < size; ++i) {
        if(!strcmp(word_list[i], remove_word)) {
            free(word_list[i]);

            for(int j = i; j < size - 1; ++j) {
                word_list[j] = word_list[j + 1];
            }

            word_list[size - 1] = NULL;
            --size;
        }
    }
}

int main() {
    int size = 5;

    char* word_list[MAX_WORD_LIST_SIZE];
    for(int i = 0; i < size; ++i) {
        word_list[i] = (char*)malloc(MAX_WORD_SIZE*sizeof(char));
    }

    strcpy(word_list[0], "word1");
    strcpy(word_list[1], "word2");
    strcpy(word_list[2], "word3");
    strcpy(word_list[3], "word4");
    strcpy(word_list[4], "word2");

    remove_specific_word(word_list, "word2", size);

    for(int i = 0; word_list[i] != NULL; ++i) {
        printf("%s\n", word_list[i]);
    }

    for(int i = 0; i < size && word_list[i] != NULL; ++i) {
        free(word_list[i]);
    }

    return 0;
}