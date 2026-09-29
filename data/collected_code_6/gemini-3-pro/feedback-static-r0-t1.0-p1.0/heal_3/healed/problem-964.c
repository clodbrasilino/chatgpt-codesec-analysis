#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = strnlen(word, max_len);
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
            if (is_length_even(word, buf_size)) {
                printf("Even\n");
            } else {
                printf("Odd\n");
            }
        }
    }

    free(word);
    return 0;
}