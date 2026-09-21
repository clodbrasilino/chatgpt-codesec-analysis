#include <stdio.h>
#include <string.h>
#include <stddef.h>

int is_word_length_odd(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    size_t length = 0;
    while (length < 1024 && word[length] != '\0') {
        length++;
    }
    
    if (word[length] != '\0') {
        length = strnlen(word, 1024);
    }
    
    return (length % 2) == 1;
}

int main(void) {
    printf("%d\n", is_word_length_odd("hello"));
    printf("%d\n", is_word_length_odd("world!"));
    printf("%d\n", is_word_length_odd("C"));
    printf("%d\n", is_word_length_odd(""));
    printf("%d\n", is_word_length_odd(NULL));
    
    return 0;
}