#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define LENGTH 30

typedef struct {
    char **words;
    int len;
} WordList;

void remove_duplicates(WordList *list) {
    for (int i = 0; i < list->len; i++) {
        for (int j = i + 1; j < list->len; j++) {
            if (strcmp(list->words[i], list->words[j]) == 0) {
                free(list->words[j]);

                for (int k = j; k < list->len - 1; k++) {
                    list->words[k] = list->words[k + 1];
                }

                list->len--;
                j--;
            }
        }
    }
}

int main(void) {
    char *rawWordList[SIZE] = {"hello", "world", "hello", "hello", "world", "test"};
    WordList list = {
        words: malloc(SIZE * sizeof(*list.words)),
        len: SIZE
    };

    if (!list.words) {
        fputs("Failed to allocate memory", stderr);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < SIZE; i++) {
        list.words[i] = malloc(LENGTH * sizeof(char));
        if (!list.words[i]) {
            fputs("Failed to allocate memory", stderr);
            return EXIT_FAILURE;
        }

        strncpy(list.words[i], rawWordList[i], LENGTH);
    }

    remove_duplicates(&list);

    for (int i = 0; i < list.len; i++) {
        puts(list.words[i]);
        free(list.words[i]);
    }

    free(list.words);

    return EXIT_SUCCESS;
}