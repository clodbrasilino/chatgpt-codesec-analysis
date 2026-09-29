#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

typedef struct {
    Word words[MAX_WORDS];
    int count;
} WordList;

void init_word_list(WordList *list) {
    list->count = 0;
}

bool is_word_in_list(WordList *list, const char *word) {
    for (int i = 0; i < list->count; ++i) {
        if (strncmp(list->words[i].word, word, MAX_WORD_LENGTH) == 0) {
            return true;
        }
    }
    return false;
}

void add_word_to_list(WordList *list, const char *word) {
    if (list->count < MAX_WORDS && !is_word_in_list(list, word)) {
        size_t word_len = strnlen(word, MAX_WORD_LENGTH);
        if (word_len < MAX_WORD_LENGTH) {
            memcpy(list->words[list->count].word, word, word_len);
            list->words[list->count].word[word_len] = '\0';
            list->count++;
        }
    }
}

char *remove_duplicate_words(const char *input) {
    WordList list;
    init_word_list(&list);

    size_t input_len = strnlen(input, MAX_WORD_LENGTH * MAX_WORDS);
    char *result = malloc(input_len + 1);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    char *token;
    char *input_copy = strdup(input);
    token = strtok(input_copy, " ");
    size_t result_len = 0;
    while (token) {
        if (!is_word_in_list(&list, token)) {
            add_word_to_list(&list, token);
            size_t token_len = strnlen(token, MAX_WORD_LENGTH);
            snprintf(result + result_len, input_len - result_len + 1, "%s ", token);
            result_len += token_len + 1;
        }
        token = strtok(NULL, " ");
    }
    free(input_copy);

    if (result_len > 0) {
        result[result_len - 1] = '\0';
    }
    return result;
}

int main() {
    const char *input = "this this is a a test test string";
    char *output = remove_duplicate_words(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}