#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char (*words)[MAX_WORD_LEN], int count, const char *word) {
    if (count < 0 || count > MAX_WORDS) {
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        if (strncmp(words[i], word, MAX_WORD_LEN - 1) == 0) {
            return 1;
        }
    }
    return 0;
}

static int remove_duplicates(const char *input[], int input_count, char (*output)[MAX_WORD_LEN]) {
    int output_count = 0;
    
    if (input == NULL || output == NULL || input_count < 0) {
        return 0;
    }
    
    for (int i = 0; i < input_count && output_count < MAX_WORDS; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        size_t len = strnlen(input[i], MAX_WORD_LEN);
        if (len >= MAX_WORD_LEN) {
            len = MAX_WORD_LEN - 1;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            if (len < MAX_WORD_LEN) {
                memcpy(output[output_count], input[i], len);
                output[output_count][len] = '\0';
            } else {
                memcpy(output[output_count], input[i], MAX_WORD_LEN - 1);
                output[output_count][MAX_WORD_LEN - 1] = '\0';
            }
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana", "date",
        "elderberry", "fig", "cherry", "grape"
    };
    int input_count = sizeof(words) / sizeof(words[0]);
    
    if (input_count > MAX_WORDS) {
        input_count = MAX_WORDS;
    }
    
    char unique_words[MAX_WORDS][MAX_WORD_LEN];
    memset(unique_words, 0, sizeof(unique_words));
    
    int unique_count = remove_duplicates(words, input_count, unique_words);
    
    printf("Original words: ");
    for (int i = 0; i < input_count; i++) {
        printf("%s ", words[i] ? words[i] : "(null)");
    }
    printf("\n");
    
    printf("Unique words: ");
    for (int i = 0; i < unique_count && i < MAX_WORDS; i++) {
        printf("%s ", unique_words[i]);
    }
    printf("\n");
    
    return 0;
}