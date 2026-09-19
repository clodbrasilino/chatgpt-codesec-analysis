#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as const array [constParameter]
 */
int is_word_in_array(char *word, char *array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array((char *)token, words, word_count)) {
            words[word_count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    char *result = (char *)malloc(strlen(input) + 1);
    result[0] = '\0';

    for (int i = 0; i < word_count; i++) {
        strcat(result, words[i]);
        strcat(result, " ");
        free(words[i]);
    }

    if (strlen(result) > 0) {
        result[strlen(result) - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    printf("%s\n", output);
    free(output);
    return 0;
}