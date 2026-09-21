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
    snprintf(set->words[set->count], sizeof(set->words[set->count]), "%s", word);
    set->count++;
    return true;
}

char* remove_duplicates(const char *input) {
    WordSet set;
    init_word_set(&set);
    char *token, *output = NULL, *temp = strdup(input), *result = NULL;
    size_t output_len = 0;
    token = strtok(temp, " ");

    while (token != NULL) {
        if (strlen(token) < MAX_WORD_LENGTH && add_word(&set, token)) {
            size_t len = strlen(token);
            output = realloc(output, (output_len + len + 2) * sizeof(char));
            if (output == NULL) {
                free(temp);
                free(result);
                return NULL;
            }
            memcpy(output + output_len, token, len + 1);
            output[output_len + len] = ' ';
            output_len += len + 1;
        }
        token = strtok(NULL, " ");
    }

    if (output) {
        if (output_len > 0) output[output_len - 1] = '\0';
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