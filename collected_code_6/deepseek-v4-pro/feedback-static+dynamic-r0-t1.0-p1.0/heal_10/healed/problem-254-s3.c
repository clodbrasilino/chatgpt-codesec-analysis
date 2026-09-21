#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 1000

static int find_words_ae(const char *str, char (*words)[MAX_WORD_LEN], int max_words) {
    if (str == NULL || words == NULL || max_words <= 0) {
        return -1;
    }
    
    int word_count = 0;
    size_t len = strnlen(str, MAX_INPUT_LEN);
    int in_word = 0;
    size_t word_start = 0;
    size_t word_len = 0;
    
    for (size_t i = 0; i <= len && word_count < max_words; i++) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
                word_len = 0;
            }
            word_len++;
            if (word_len >= MAX_WORD_LEN) {
                in_word = 0;
                word_len = 0;
            }
        } else {
            if (in_word) {
                if (word_len > 0 && word_len < MAX_WORD_LEN) {
                    char first_char = tolower((unsigned char)str[word_start]);
                    if (first_char == 'a' || first_char == 'e') {
                        size_t copy_len = word_len;
                        if (copy_len >= MAX_WORD_LEN) {
                            copy_len = MAX_WORD_LEN - 1;
                        }
                        if (word_start + copy_len <= len && word_start < len) {
                            memcpy(words[word_count], str + word_start, copy_len);
                            words[word_count][copy_len] = '\0';
                            word_count++;
                        }
                    }
                }
                in_word = 0;
                word_len = 0;
            }
        }
    }
    
    return word_count;
}

int main(void) {
    char input[MAX_INPUT_LEN + 1] = {0};
    char words[MAX_WORDS][MAX_WORD_LEN] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else {
        int found_newline = 0;
        for (size_t i = 0; i < input_len; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                found_newline = 1;
                input_len = i;
                break;
            }
        }
        if (!found_newline) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }
    }
    
    if (input_len >= MAX_INPUT_LEN) {
        input[MAX_INPUT_LEN] = '\0';
    }
    
    int count = find_words_ae(input, words, MAX_WORDS);
    
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