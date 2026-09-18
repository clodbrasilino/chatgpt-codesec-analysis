#include<stdio.h>
#include<string.h>

#define MAX_STR_SIZE 100
#define MAX_WORD_SIZE 50

struct count_word {
    char word[MAX_WORD_SIZE];
    int count;
};

void find_most_common_word(char strings[][MAX_STR_SIZE], int len, char *result) {
    struct count_word words[len * MAX_STR_SIZE];
    int words_count = 0;
    
    for(int i=0; i<len; i++) {
        char *token = strtok(strings[i], " ");
        
        while(token != NULL) {
            int found = 0;
            
            for(int j = 0; j < words_count && !found; j++) {
                if(strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                }
            }
            
            if(!found) {
                strcpy(words[words_count].word, token);
                words[words_count].count = 1;
                words_count++;
            }
            token = strtok(NULL, " ");
        }
    }
    
    int max_count_index = 0;
    for(int i = 0; i < words_count; i++) {
        if(words[i].count > words[max_count_index].count) {
            max_count_index = i;
        }
    }
    strcpy(result, words[max_count_index].word);
}

int main() {
    char strings[4][MAX_STR_SIZE] = {"hello world", "world is beautiful", "beautiful world", "hello everyone"};
    char result[MAX_WORD_SIZE];
    find_most_common_word(strings, 4, result);
    printf("The word with most occurrences is: %s\n", result);
    return 0;
} 