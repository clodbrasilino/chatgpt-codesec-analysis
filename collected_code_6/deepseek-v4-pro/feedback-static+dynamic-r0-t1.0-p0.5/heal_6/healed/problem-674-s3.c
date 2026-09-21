#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

void to_lowercase(char *str) {
    while (*str) {
        *str = (char)tolower((unsigned char)*str);
        str++;
    }
}

int word_exists(const WordList *list, const char *word) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t word_len = strlen(word);
    if (word_len >= MAX_WORD_LEN) {
        word_len = MAX_WORD_LEN - 1;
    }
    
    memcpy(list->words[list->count], word, word_len);
    list->words[list->count][word_len] = '\0';
    list->count++;
    return 1;
}

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len >= 1000000) {
        return NULL;
    }

    if (input_len == 0) {
        char *empty_result = malloc(1);
        if (empty_result != NULL) {
            empty_result[0] = '\0';
        }
        return empty_result;
    }

    WordList seen;
    memset(&seen, 0, sizeof(seen));

    size_t result_capacity = input_len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    size_t result_len = 0;

    char *temp = malloc(input_len + 1);
    if (temp == NULL) {
        free(result);
        return NULL;
    }
    
    memcpy(temp, input, input_len + 1);

    char *token = strtok(temp, " \t\n\r");
    int first = 1;

    while (token != NULL) {
        char lower_word[MAX_WORD_LEN];
        size_t token_len = strlen(token);
        if (token_len >= MAX_WORD_LEN) {
            token_len = MAX_WORD_LEN - 1;
        }
        
        memcpy(lower_word, token, token_len);
        lower_word[token_len] = '\0';
        to_lowercase(lower_word);

        if (!word_exists(&seen, lower_word)) {
            add_word(&seen, lower_word);

            size_t needed_len = result_len + (first ? 0 : 1) + token_len + 1;
            if (needed_len > result_capacity) {
                size_t new_capacity = needed_len * 2;
                if (new_capacity < needed_len) {
                    free(result);
                    free(temp);
                    return NULL;
                }
                char *new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    free(temp);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }

            if (!first) {
                result[result_len] = ' ';
                result_len++;
            }
            
            memcpy(result + result_len, token, token_len);
            result_len += token_len;
            result[result_len] = '\0';
            first = 0;
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(temp);
    return result;
}

int main(void) {
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *result = remove_duplicate_words(input);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Result: %s\n", result);
    free(result);

    return 0;
}