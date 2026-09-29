#include <stdio.h>
#include <ctype.h>
#include <string.h>

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int max_length = 0;
    int current_length = 0;
    int in_word = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i]) || str[i] == '\'') {
            if (!in_word) {
                in_word = 1;
                current_length = 0;
            }
            current_length++;
        } else {
            if (in_word) {
                if (current_length > max_length) {
                    max_length = current_length;
                }
                in_word = 0;
                current_length = 0;
            }
        }
    }
    
    if (in_word && current_length > max_length) {
        max_length = current_length;
    }
    
    return max_length;
}

int main(void) {
    const char *test_strings[] = {
        "The quick brown fox jumps over the lazy dog",
        "",
        "Hello World",
        "Testing   multiple   spaces",
        "A",
        "Supercalifragilisticexpialidocious is a long word",
        "word1 word22 word333 word4444",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        printf("String: \"%s\"\n", test_strings[i]);
        printf("Longest word length: %d\n\n", longest_word_length(test_strings[i]));
    }
    
    printf("Testing NULL pointer:\n");
    printf("Longest word length: %d\n", longest_word_length(NULL));
    
    return 0;
}