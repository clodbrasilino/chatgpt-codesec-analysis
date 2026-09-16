#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

int find_words_ae(const char *str, char words[][MAX_WORD_LEN]) {
    if (str == NULL || words == NULL) {
        return -1;
    }
    
    int word_count = 0;
    int len = strlen(str);
    int in_word = 0;
    int word_start = 0;
    int word_len = 0;
    char current_word[MAX_WORD_LEN];
    
    for (int i = 0; i <= len; i++) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
                word_len = 0;
            }
            word_len++;
        } else {
            if (in_word) {
                if (word_len < MAX_WORD_LEN) {
                    strncpy(current_word, str + word_start, word_len);
                    current_word[word_len] = '\0';
                    
                    if (tolower((unsigned char)current_word[0]) == 'a' || 
                        tolower((unsigned char)current_word[0]) == 'e') {
                        if (word_count < MAX_WORDS) {
                            strcpy(words[word_count], current_word);
                            word_count++;
                        }
                    }
                }
                in_word = 0;
            }
        }
    }
    
    return word_count;
}

int main(void) {
    char input[1000];
    char words[MAX_WORDS][MAX_WORD_LEN];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    int count = find_words_ae(input, words);
    
    if (count < 0) {
        printf("Error processing input\n");
        return 1;
    }
    
    printf("Words starting with 'a' or 'e':\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    
    return 0;
}