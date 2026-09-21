#include <stdio.h>
#include <string.h>

int is_word_length_odd(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(word);
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