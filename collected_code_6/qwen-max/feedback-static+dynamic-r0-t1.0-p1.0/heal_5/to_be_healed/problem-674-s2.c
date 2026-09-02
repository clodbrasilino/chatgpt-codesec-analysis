#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    bool exists;
} Word;

Word dictionary[MAX_WORDS] = {0};

int add_word(const char *word) {
    for (int i = 0; i < MAX_WORDS; ++i) {
        if (!dictionary[i].exists) {
            strncpy(dictionary[i].word, word, MAX_WORD_LENGTH - 1);
            dictionary[i].word[MAX_WORD_LENGTH - 1] = '\0';
            dictionary[i].exists = true;
            return i;
        }
    }
    return -1;
}

bool is_duplicate(const char *word) {
    for (int i = 0; i < MAX_WORDS; ++i) {
        if (dictionary[i].exists && strcmp(dictionary[i].word, word) == 0) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got 
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got 
  */

char* remove_duplicates(char *input) {
    if (input == NULL) return NULL;

    char *output = (char *)malloc(strlen(input) * 2 + 1);
    if (output == NULL) return NULL;

    char *token = strtok(input, " ");
    int output_index = 0;

    while (token != NULL) {
        if (!is_duplicate(token)) {
            int len = strlen(token);
            strncpy(output + output_index, token, len);
            output[output_index + len] = ' ';
            output_index += len + 1;
            add_word(token);
        }
        token = strtok(NULL, " ");
    }

    if (output_index > 0 && output[output_index - 1] == ' ') {
        output[output_index - 1] = '\0';
    } else {
        output[0] = '\0';
    }

    return output;
}

int main() {
    char input[] = "hello world hello C programming C";
    char *result = remove_duplicates(input);
    printf("%s\n", result);
    free(result);
    return 0;
}