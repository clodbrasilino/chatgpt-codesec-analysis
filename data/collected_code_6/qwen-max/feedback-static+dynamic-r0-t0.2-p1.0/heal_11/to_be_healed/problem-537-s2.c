#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got ca ab bc
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(const char *str) {
    const int max_words = 1024;
    char **words = (char **)malloc(max_words * sizeof(char *));
    if (!words) return NULL;
    bool *seen = (bool *)calloc(max_words, sizeof(bool));
    if (!seen) {
        free(words);
        return NULL;
    }
    int word_count = 0;

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        if (start == p) break;

        bool found = false;
        for (int i = 0; i < word_count; i++) {
            if (strncmp(words[i], start, p - start) == 0) {
                /* Possible weaknesses found:
                 *  Variable 'found' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'found' is never read [deadcode.DeadStores]
                 */
                found = true;
                free(words);
                free(seen);
                return (char *)start;
            }
        }
        if (!found && word_count < max_words) {
            words[word_count] = (char *)malloc((p - start + 1) * sizeof(char));
            if (words[word_count]) {
                memcpy(words[word_count], start, p - start);
                words[word_count][p - start] = '\0';
                seen[word_count++] = true;
            } else {
                free(words);
                free(seen);
                return NULL;
            }
        } else if (word_count >= max_words) {
            free(words);
            free(seen);
            return NULL;
        }

        if (*p) p++;
    }

    free(words);
    free(seen);
    return NULL;
}

int main() {
    const char *input = "ca ab bc ca";
    char *result = find_first_repeated_word(input);
    if (result) {
        const char *end = strchr(result, ' ');
        if (end) {
            printf("First repeated word: %.*s\n", (int)(end - result), result);
        } else {
            printf("First repeated word: %s\n", result);
        }
    } else {
        printf("None\n");
    }

    const char *input2 = "a b c d e f g h i j k l m n o p q r s t u v w x y z a";
    result = find_first_repeated_word(input2);
    if (result) {
        const char *end = strchr(result, ' ');
        if (end) {
            printf("First repeated word: %.*s\n", (int)(end - result), result);
        } else {
            printf("First repeated word: %s\n", result);
        }
    } else {
        printf("None\n");
    }

    const char *input3 = "unique words only";
    result = find_first_repeated_word(input3);
    if (result) {
        const char *end = strchr(result, ' ');
        if (end) {
            printf("First repeated word: %.*s\n", (int)(end - result), result);
        } else {
            printf("First repeated word: %s\n", result);
        }
    } else {
        printf("None\n");
    }

    return 0;
}