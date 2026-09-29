#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Word {
    char word[50];
    int count;
} Word;

void add_word(Word words[], int* pIndex, char *word) {
    for(int i = 0; i < *pIndex; i++) {
        if(strcmp(words[i].word, word) == 0) {
            words[i].count++;
            return;
        }
    }
    Word temp;
    strcpy(temp.word, word);
    temp.count = 1;
    words[*pIndex] = temp;
    (*pIndex)++;
}

int comparator(const void* p, const void* q){
    return strcmp(((Word*)p)->word,((Word*)q)->word);
}

int main(void) {
    Word words[5000];
    int index = 0;
    char str[1000];
    printf("Enter the text: ");
    fgets(str, 1000, stdin);
    char* word = strtok(str," ,.-!?");
    while(word != NULL) {
        add_word(words, &index, word);
        word = strtok(NULL, " ,.-!?");
    }
    qsort((void*) words, index, sizeof(words[0]), comparator);

    int N;
    printf("Enter the number of most common words: ");
    scanf("%d",&N);

    printf("The most common words are: ");

    for(int i = index-N; i < index; i++)
        printf("%s ", words[i].word);
    return 0;
}