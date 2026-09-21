#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    const int max_words = 1024;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[max_words];
    bool seen[max_words] = {false};
    int word_count = 0;

    for (int i = 0; i < max_words; i++) {
        words[i] = NULL;
    }

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        if (start == p) break;

        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], start) == 0) {
                return (char *)start;
            }
        }

        if (word_count < max_words) {
            int len = p - start;
            words[word_count] = (char *)malloc(len + 1);
            if (words[word_count] == NULL) {
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(words[word_count], start, len);
            words[word_count][len] = '\0';
            seen[word_count++] = true;
        } else {
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            return NULL;
        }

        if (*p) p++;
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }

    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in this string";
    char *result = find_first_repeated_word(input);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}