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
    strncpy(set->words[set->count], word, MAX_WORD_LENGTH - 1);
    set->words[set->count][MAX_WORD_LENGTH - 1] = '\0';
    set->count++;
    return true;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    WordSet set;
    init_word_set(&set);
    char *token, *output = NULL, *temp = strdup(input);
    token = strtok(temp, " ");
    while (token != NULL) {
        if (add_word(&set, token)) {
            int len = strlen(token) + 2;
            char *new_output = realloc(output, (strlen(output ? output : "") + len));
            if (new_output == NULL) {
                free(output);
                free(temp);
                return NULL;
            }
            output = new_output;
            if (output[0] == '\0') {
                strcat(output, token);
                strcat(output, " ");
            } else {
                strcat(output, " ");
                strcat(output, token);
            }
        }
        token = strtok(NULL, " ");
    }
    if (output) {
        output[strlen(output) - 1] = '\0';
        char *result = strdup(output);
        free(output);
        free(temp);
        return result;
    }
    free(temp);
    return NULL;
}

int main() {
    const char *input = "Python Exercises Practice Solution";
    char *result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Allocation failed.\n");
    }
    input = "this is a test this is only a test";
    result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Allocation failed.\n");
    }
    return 0;
}