#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

int find_word(struct WordCount wc[], int n, char *word) {
    for(int i = 0; i < n; i++) {
        if(strcmp(wc[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void most_frequent_word(char *strings[], int n, char *output_word) {
    struct WordCount wc[MAX_WORDS];
    int wc_count = 0;

    for(int i = 0; i < n; i++) {
        char *word = strtok(strings[i], " ");
        while(word != NULL) {
            int index = find_word(wc, wc_count, word);
            if(index == -1) {
                strcpy(wc[wc_count].word, word);
                wc[wc_count].count = 1;
                wc_count++;
            } else {
                wc[index].count++;
            }
            word = strtok(NULL, " ");
        }
    }

    int max_count_index = 0;
    for(int i = 1; i < wc_count; i++) {
        if(wc[i].count > wc[max_count_index].count) {
            max_count_index = i;
        }
    }

    strcpy(output_word, wc[max_count_index].word);
}

int main() {
    char *strings[] = {"hello world", "world is beautiful", "hello everyone", "hello world"};
    int n = sizeof(strings) / sizeof(strings[0]);
    char output_word[MAX_WORD_LENGTH];

    most_frequent_word(strings, n, output_word);
    printf("Most frequent word: %s\n", output_word);

    return 0;
}