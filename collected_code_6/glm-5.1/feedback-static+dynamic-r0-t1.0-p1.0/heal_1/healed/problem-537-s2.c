#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (!words) {
        return NULL;
    }

    size_t word_count = 0;
    char *input = strdup(str);
    if (!input) {
        free(words);
        return NULL;
    }

    char *token = strtok(input, " ,.;:!?()-\t\n\r");
    while (token != NULL && word_count < MAX_WORDS) {
        for (int i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        for (size_t i = 0; i < word_count; i++) {
            if (words[i] && strcmp(words[i], token) == 0) {
                char *result = strdup(token);
                free(input);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                return result ? result : strdup("");
            }
        }

        words[word_count] = strdup(token);
        if (!words[word_count]) {
            free(input);
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(words);
            return strdup("");
        }
        word_count++;
        token = strtok(NULL, " ,.;:!?()-\t\n\r");
    }

    free(input);
    for (size_t j = 0; j < word_count; j++) {
        free(words[j]);
    }
    free(words);
    return strdup("");
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(text);
    
    if (repeated && *repeated) {
        printf("%s\n", repeated);
    } else {
        printf("None\n");
    }
    
    free(repeated);
    return 0;
}