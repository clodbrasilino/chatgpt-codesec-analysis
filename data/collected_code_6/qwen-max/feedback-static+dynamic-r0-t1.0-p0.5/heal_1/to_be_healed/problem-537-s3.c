#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  *  test case 2 failed: expected 'ca', got bc
  */

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    bool seen[MAX_WORDS] = {false};
    int word_count = 0;

    const char *p = str;
    while (*p) {
        if (word_count >= MAX_WORDS) break;

        const char *start = p;
        while (*p && *p != ' ') p++;

        int len = p - start;
        if (len > 0 && len < MAX_WORD_LENGTH) {
            for (int i = 0; i < word_count; i++) {
                if (strcmp(words[i], start) == 0) {
                    return (char *)start;
                }
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[word_count], start, len);
            words[word_count][len] = '\0';
            /* Possible weaknesses found:
             *  Variable 'seen[word_count]' is assigned a value that is never used. [unreadVariable]
             */
            seen[word_count] = true;
            word_count++;
        }

        while (*p == ' ') p++;
    }

    return NULL;
}

int main() {
    const char *input = "This is a test string with a repeated word and the word is repeated";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}