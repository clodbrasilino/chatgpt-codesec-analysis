#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define WORD_LEN 50
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got 
  *  test case 2 failed: expected 'ca', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][WORD_LEN] = {0};
    int word_count = 0;
    char *token, *copy_str = strdup(str);
    bool found = false;

    token = strtok(copy_str, " ");
    while (token != NULL && !found) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                free(copy_str);
                return (char *)token;
            }
        }
        strncpy(words[word_count++], token, WORD_LEN - 1);
        token = strtok(NULL, " ");
    }

    free(copy_str);
    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result != NULL) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}