#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define LIST_LENGTH 100

char* get_most_frequent_word(char* list[], int length) {
    int i, j, max_count = -1;
    char* word = malloc(sizeof(char) * MAX_WORD_LENGTH);
    char* most_freq_word = malloc(sizeof(char) * MAX_WORD_LENGTH);

    for(i = 0; i < length; ++i) {
        int count = 0;
        for(j = 0; j < length; ++j) {
            if(strcmp(list[i], list[j]) == 0)
                ++count;
        }

        if(count > max_count) {
            max_count = count;
            strcpy(most_freq_word, list[i]);
        }
    }

    /* Possible weaknesses found:
     *  leak of 'word' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return most_freq_word;
}

int main() {
    char* list[LIST_LENGTH] = {"apple", "banana", "apple", "orange", "banana","apple"};
    char* most_freq_word = get_most_frequent_word(list, 6);

    printf("The word with most occurrences is: %s\n", most_freq_word);

    free(most_freq_word);

    return 0;
}