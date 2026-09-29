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

bool add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return false;
    }
    for (int i = 0; i < list->count; ++i) {
        if (strcmp(list->words[i].word, word) == 0) {
            return false;
        }
    }
    snprintf(list->words[list->count].word, sizeof(list->words[list->count].word), "%.*s", (int)strnlen(word, MAX_WORD_LENGTH), word);
    list->count++;
    return true;
}

char *remove_duplicates(const char *input) {
    WordList list;
    init_word_list(&list);

    const char *token;
    const char *context = NULL;
    char *input_copy = strdup(input);
    token = strtok_r(input_copy, " ", (char **)&context);

    size_t input_len = strnlen(input, MAX_WORD_LENGTH * MAX_WORDS + 1);
    char *result = (char *)malloc(input_len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    while (token) {
        if (add_word(&list, token)) {
            size_t token_len = strnlen(token, MAX_WORD_LENGTH);
            size_t result_len = strnlen(result, MAX_WORD_LENGTH * MAX_WORDS + 1);
            if (input_len - (result_len + token_len + 1) >= 0) {
                strncat(result, token, token_len);
                strncat(result, " ", 1);
            }
        }
        token = strtok_r(NULL, " ", (char **)&context);
    }
    free(input_copy);

    size_t result_len = strnlen(result, MAX_WORD_LENGTH * MAX_WORDS + 1);
    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[result_len - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}