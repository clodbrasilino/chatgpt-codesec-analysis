#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define WORD_LEN 50
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][WORD_LEN] = {0};
    int word_count = 0;
    char *token, *copy_str = strdup(str);
    if (copy_str == NULL) return NULL;

    token = strtok(copy_str, " ");
    while (token != NULL) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                free(copy_str);
                return strdup(token);
            }
        }
        strncpy(words[word_count], token, WORD_LEN - 1);
        words[word_count][strnlen(token, WORD_LEN - 1)] = '\0';
        word_count++;
        if (word_count >= MAX_WORDS) break;
        token = strtok(NULL, " ");
    }

    free(copy_str);
    return NULL;
}

int main() {
    const char *input1 = "";
    const char *input2 = "a b a";
    const char *input3 = "c a c";

    char *result1 = find_first_repeated_word(input1);
    if (result1 != NULL) {
        printf("First repeated word: %s\n", result1);
        free(result1);
    } else {
        printf("None\n");
    }

    char *result2 = find_first_repeated_word(input2);
    if (result2 != NULL) {
        printf("First repeated word: %s\n", result2);
        free(result2);
    } else {
        printf("\n");
    }

    char *result3 = find_first_repeated_word(input3);
    if (result3 != NULL) {
        printf("First repeated word: %s\n", result3);
        free(result3);
    } else {
        printf("None\n");
    }

    return 0;
}