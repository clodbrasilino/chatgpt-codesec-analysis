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
        if (strcmp(list->words[i].word, word) == 0) {
            return true;
        }
    }
    return false;
}

void add_word_to_list(WordList *list, const char *word) {
    if (list->count < MAX_WORDS && !is_word_in_list(list, word)) {
        strcpy(list->words[list->count].word, word);
        list->count++;
    }
}

char *remove_duplicate_words(const char *input) {
    WordList list;
    init_word_list(&list);

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    char *token = strtok((char *)input, " ");
    size_t result_len = 0;
    while (token) {
        if (!is_word_in_list(&list, token)) {
            add_word_to_list(&list, token);
            size_t token_len = strlen(token);
            strncat(result, token, token_len);
            result[result_len + token_len] = ' ';
            result_len += token_len + 1;
        }
        token = strtok(NULL, " ");
    }

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