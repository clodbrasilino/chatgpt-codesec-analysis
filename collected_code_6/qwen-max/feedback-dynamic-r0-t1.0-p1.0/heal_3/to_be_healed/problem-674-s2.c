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
        if (strcmp(set->words[i], word) == 0) return false;
    }
    strncpy(set->words[set->count], word, MAX_WORD_LENGTH - 1);
    set->words[set->count][MAX_WORD_LENGTH - 1] = '\0';
    set->count++;
    return true;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    WordSet set;
    init_word_set(&set);
    char *token, *output = NULL, *temp = strdup(input), *result = NULL;
    token = strtok(temp, " ");
    while (token != NULL) {
        if (add_word(&set, token)) {
            if (output == NULL) {
                output = malloc((strlen(token) + 1) * sizeof(char));
            } else {
                output = realloc(output, (strlen(output) + strlen(token) + 2) * sizeof(char));
            }
            if (output == NULL) {
                free(temp);
                return NULL;
            }
            if (output && strlen(output) > 0) strcat(output, " ");
            strcat(output, token);
        }
        token = strtok(NULL, " ");
    }
    if (output) {
        result = strdup(output);
        free(output);
    }
    free(temp);
    return result;
}

int main() {
    const char *inputs[] = {"Python Exercises Practice Solution", "this is a test this is only a test", "hello world hello"};
    for (int i = 0; i < 3; i++) {
        char *result = remove_duplicates(inputs[i]);
        if (result) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Error: Allocation failed.\n");
        }
    }
    return 0;
}