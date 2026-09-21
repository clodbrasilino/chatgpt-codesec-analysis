#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_five_char_words(const char *input) {
    const char *cursor = input;
    size_t len = strlen(input);
    
    while (cursor < input + len) {
        while (*cursor != '\0' && !((*cursor >= 'a' && *cursor <= 'z') || 
                                     (*cursor >= 'A' && *cursor <= 'Z'))) {
            cursor++;
        }
        
        if (*cursor == '\0') break;
        
        const char *start = cursor;
        size_t word_len = 0;
        
        while (*cursor != '\0' && ((*cursor >= 'a' && *cursor <= 'z') || 
                                    (*cursor >= 'A' && *cursor <= 'Z'))) {
            word_len++;
            cursor++;
        }
        
        if (word_len == 5) {
            char *word = (char *)malloc(word_len + 1);
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return;
            }
            
            if (word_len < 1024) {
                memcpy(word, start, word_len);
                word[word_len] = '\0';
                printf("%s\n", word);
            }
            
            free(word);
        }
    }
}

int main(void) {
    char input[1024];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }

    find_five_char_words(input);

    return EXIT_SUCCESS;
}