#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int count;
} WordSet;

void init_word_set(WordSet *set) {
    set->count = 0;
}

bool add_word(WordSet *set, const char *word) {
    if (set->count >= MAX_WORDS) return false;
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->words[i], word) == 0) return true;
    }
    size_t word_len = strnlen(word, MAX_WORD_LENGTH);
    if (word_len >= MAX_WORD_LENGTH - 1) return false;
    memcpy(set->words[set->count], word, word_len + 1);
    set->count++;
    return true;
}

char* remove_duplicates(const char *input) {
    WordSet set;
    init_word_set(&set);
    char *token, *output = NULL, *temp = strdup(input), *result = NULL;
    token = strtok(temp, " ");
    while (token != NULL) {
        if (add_word(&set, token)) {
            size_t len = strnlen(token, MAX_WORD_LENGTH) + 1;
            char *new_output = realloc(output, (output ? strlen(output) : 0) + len + 1);
            if (new_output == NULL) {
                free(temp);
                free(output);
                return NULL;
            }
            output = new_output;
            memmove(output + (output ? strlen(output) : 0), token, len - 1);
            memmove(output + (output ? strlen(output) : 0) + len - 1, " ", 1);
        }
        token = strtok(NULL, " ");
    }
    if (output) {
        output[strnlen(output, MAX_WORD_LENGTH) - 1] = '\0';
        result = strdup(output);
        free(output);
    }
    free(temp);
    return result;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Allocation failed.\n");
    }
    return 0;
}