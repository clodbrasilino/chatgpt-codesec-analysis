#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void find_words_starting_with_a_or_e(const char *str) {
    const char *p = str;
    size_t buffer_size = 256;
    char *word = malloc(buffer_size);
    
    if (word == NULL) {
        return;
    }

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        
        size_t i = 0;
        while (*p && isalpha((unsigned char)*p)) {
            if (i >= buffer_size - 1) {
                size_t new_size = buffer_size * 2;
                char *new_word = realloc(word, new_size);
                if (new_word == NULL) {
                    free(word);
                    return;
                }
                word = new_word;
                buffer_size = new_size;
            }
            word[i++] = *p++;
        }
        word[i] = '\0';
        
        if (i > 0 && (word[0] == 'a' || word[0] == 'e' || word[0] == 'A' || word[0] == 'E')) {
            printf("%s\n", word);
        }
    }
    
    free(word);
}

int main(void) {
    size_t buffer_size = 1024;
    char *str = malloc(buffer_size);
    
    if (str == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    
    size_t len = 0;
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len >= buffer_size - 1) {
            size_t new_size = buffer_size * 2;
            char *new_str = realloc(str, new_size);
            if (new_str == NULL) {
                free(str);
                return 1;
            }
            str = new_str;
            buffer_size = new_size;
        }
        str[len++] = (char)c;
    }
    str[len] = '\0';

    find_words_starting_with_a_or_e(str);

    free(str);
    return 0;
}