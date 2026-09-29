#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

int is_duplicate(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < list->count; i++) {
        if (strncmp(list->words[i], word, MAX_WORD_LEN - 1) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t len = strlen(word);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }
    
    if (len > 0) {
        memcpy(list->words[list->count], word, len);
    }
    list->words[list->count][len] = '\0';
    list->count++;
    return 1;
}

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t input_len = strlen(str);
    char *input_copy = malloc(input_len + 1);
    if (input_copy == NULL) {
        return NULL;
    }
    memcpy(input_copy, str, input_len + 1);

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        free(input_copy);
        return NULL;
    }
    output[0] = '\0';

    WordList seen;
    memset(&seen, 0, sizeof(seen));

    char *saveptr;
    char *token = strtok_r(input_copy, " \t\n\r", &saveptr);
    int first = 1;

    while (token != NULL) {
        if (!is_duplicate(&seen, token)) {
            add_word(&seen, token);
            if (!first) {
                size_t current_len = strlen(output);
                if (current_len < input_len) {
                    output[current_len] = ' ';
                    output[current_len + 1] = '\0';
                }
            }
            size_t token_len = strlen(token);
            size_t current_len = strlen(output);
            size_t space_remaining = input_len - current_len;
            if (token_len < space_remaining) {
                memcpy(output + current_len, token, token_len + 1);
            }
            first = 0;
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }

    free(input_copy);
    return output;
}

int main(void) {
    const char *test_strings[] = {
        "hello world hello again world test hello",
        "Python Exercises Practice Solution",
        "Python Exercises Practice Solution",
        "Python Exercises Practice Solution",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("Original: %s\n", test_strings[i]);
        char *result = remove_duplicate_words(test_strings[i]);
        if (result != NULL) {
            printf("After removing duplicates: %s\n", result);
            free(result);
        }
    }

    return 0;
}