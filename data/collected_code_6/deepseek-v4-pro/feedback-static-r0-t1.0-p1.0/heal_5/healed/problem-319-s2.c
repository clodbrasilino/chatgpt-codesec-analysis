#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 1024

void find_five_char_words(const char *input) {
    if (input == NULL) {
        return;
    }
    
    const char *cursor = input;
    
    while (*cursor != '\0') {
        while (*cursor != '\0' && !isalpha((unsigned char)*cursor)) {
            cursor++;
        }
        
        if (*cursor == '\0') {
            break;
        }
        
        const char *start = cursor;
        size_t word_len = 0;
        
        while (*cursor != '\0' && isalpha((unsigned char)*cursor)) {
            word_len++;
            cursor++;
        }
        
        if (word_len == 5) {
            char *word = (char *)malloc(word_len + 1);
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return;
            }
            
            if (word_len < INPUT_BUFFER_SIZE) {
                memcpy(word, start, word_len);
                word[word_len] = '\0';
                printf("%s\n", word);
            }
            
            free(word);
        }
    }
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    find_five_char_words(input);

    return EXIT_SUCCESS;
}