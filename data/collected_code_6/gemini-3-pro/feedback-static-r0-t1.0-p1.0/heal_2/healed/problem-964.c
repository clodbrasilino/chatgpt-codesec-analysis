#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = strlen(word);
    return (length % 2 == 0);
}

int main(void) {
    size_t buf_size = MAX_WORD_LEN;
    char *word = (char *)malloc(buf_size);

    if (word == NULL) {
        return 1;
    }

    if (fgets(word, (int)buf_size, stdin) != NULL) {
        word[strcspn(word, " \t\r\n")] = '\0';
        
        if (word[0] != '\0') {
            if (is_length_even(word)) {
                printf("Even\n");
            } else {
                printf("Odd\n");
            }
        }
    }

    free(word);
    return 0;
}