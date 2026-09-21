#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1024
#define WORD_LEN 64
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (!words) return NULL;
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = (char *)malloc(WORD_LEN * sizeof(char));
        if (!words[i]) {
            for (int j = 0; j < i; j++) free(words[j]);
            free(words);
            return NULL;
        }
    }
    int word_count = 0;
    const char *p = str;
    bool found = false;

    while (*p) {
        if (word_count >= MAX_WORDS) break;
        if (*p == ' ' || *p == '\t' || *p == '\n') {
            p++;
            continue;
        }
        int idx = 0;
        while (*p && *p != ' ' && *p != '\t' && *p != '\n' && idx < WORD_LEN - 1) {
            words[word_count][idx++] = *p++;
        }
        words[word_count][idx] = '\0';

        for (int j = 0; j < word_count; j++) {
            if (strcmp(words[j], words[word_count]) == 0) {
                found = true;
                break;
            }
        }

        if (found) {
            for (int k = 0; k < MAX_WORDS; k++) {
                free(words[k]);
            }
            free(words);
            return strdup(words[word_count]);
        }

        word_count++;
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    return NULL;
}

int main() {
    const char *inputs[] = {"ab ca bc ab", "a b c d e f g h a", "x y z a b c x"};
    for (int i = 0; i < 3; i++) {
        char *result = find_first_repeated_word(inputs[i]);
        if (result) {
            printf("First repeated word: %s\n", result);
            free(result);
        } else {
            printf("No repeated word found.\n");
        }
    }
    return 0;
}