#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_OUTPUT_LEN (MAX_WORDS * MAX_WORD_LEN)

typedef struct {
    char *words[MAX_WORDS];
    int count;
} WordList;

void init_word_list(WordList *list) {
    list->count = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        list->words[i] = NULL;
    }
}

void free_word_list(WordList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->words[i]);
        list->words[i] = NULL;
    }
    list->count = 0;
}

int contains_word(WordList *list, const char *word) {
    if (word == NULL) return 0;
    for (int i = 0; i < list->count; i++) {
        if (list->words[i] != NULL && strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS || word == NULL) {
        return 0;
    }
    
    size_t len = strlen(word);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }
    
    char *new_word = malloc(len + 1);
    if (new_word == NULL) {
        return 0;
    }
    
    memcpy(new_word, word, len);
    new_word[len] = '\0';
    
    list->words[list->count] = new_word;
    list->count++;
    return 1;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    WordList seen;
    init_word_list(&seen);
    
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    output[0] = '\0';
    
    size_t input_len = strlen(input);
    if (input_len == 0) {
        return;
    }
    
    char *copy = malloc(input_len + 1);
    if (copy == NULL) {
        return;
    }
    memcpy(copy, input, input_len + 1);
    
    char *result = malloc(MAX_OUTPUT_LEN);
    if (result == NULL) {
        free(copy);
        return;
    }
    result[0] = '\0';
    
    char *saveptr;
    char *token = strtok_r(copy, " \t\n\r", &saveptr);
    int first = 1;
    size_t result_len = 0;
    
    while (token != NULL) {
        if (!contains_word(&seen, token)) {
            add_word(&seen, token);
            size_t token_len = strlen(token);
            size_t space_needed = first ? 0 : 1;
            
            if (result_len + space_needed + token_len + 1 <= MAX_OUTPUT_LEN) {
                if (!first) {
                    result[result_len] = ' ';
                    result_len++;
                }
                memcpy(result + result_len, token, token_len);
                result_len += token_len;
                result[result_len] = '\0';
                first = 0;
            } else {
                break;
            }
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }
    
    size_t copy_len = result_len;
    if (copy_len >= output_size) {
        copy_len = output_size - 1;
    }
    memcpy(output, result, copy_len);
    output[copy_len] = '\0';
    
    free_word_list(&seen);
    free(result);
    free(copy);
}

int main(void) {
    char input[2048];
    char output[2048];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    remove_duplicate_words(input, output, sizeof(output));

    printf("Original: %s\n", input);
    printf("After removing duplicates: %s\n", output);

    return 0;
}