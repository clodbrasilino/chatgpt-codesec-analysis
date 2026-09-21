#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = 0;
    while (length < max_len && word[length] != '\0' && word[length] != '\n') {
        length++;
    }
    
    return (length % 2 == 0);
}

int main(void) {
    size_t max_size = 256;
    char *word = (char *)malloc(max_size * sizeof(char));

    if (word == NULL) {
        return 1;
    }

    if (fgets(word, max_size, stdin) != NULL) {
        if (is_length_even(word, max_size)) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }

    free(word);
    return 0;
}