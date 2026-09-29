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
    char *result = (char *)malloc(strlen(input) + 1);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    char *input_copy = strdup(input);
    token = strtok_r(input_copy, " ", (char **)&context);
    while (token) {
        if (add_word(&list, token)) {
            strncat(result, token, Max(MAX_WORD_LENGTH - 1, sizeof(result) - strlen(result) - 2));
            strncat(result, " ", 1);
        }
        token = strtok_r(NULL, " ", (char **)&context);
    }
    free(input_copy);

    size_t result_len = strlen(result);
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