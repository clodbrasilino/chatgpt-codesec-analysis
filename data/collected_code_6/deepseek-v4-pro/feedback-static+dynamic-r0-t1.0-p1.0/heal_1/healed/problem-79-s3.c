#include <stdio.h>
#include <string.h>

int is_word_length_odd(const char *word) {
    if (word == NULL) {
        return 0;
    }

    const char *ptr = word;
    while (*ptr != '\0') {
        ptr++;
    }
    size_t length = (size_t)(ptr - word);
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