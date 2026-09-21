#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(char *str) {
    if (!str) {
        return NULL;
    }
    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *copy = strdup(str);
    if (!copy) {
        return NULL;
    }
    char *rest = copy;
    while (*rest) {
        while (*rest && (isspace((unsigned char)*rest) || ispunct((unsigned char)*rest))) {
            rest++;
        }
        if (!*rest) {
            break;
        }
        char *token = rest;
        while (*rest && !isspace((unsigned char)*rest) && !ispunct((unsigned char)*rest)) {
            *rest = tolower((unsigned char)*rest);
            rest++;
        }
        if (*rest) {
            *rest = '\0';
            rest++;
        }
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                char *result = strdup(token);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                free(copy);
                return result;
            }
        }
        if (word_count >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char **new_words = realloc(words, new_capacity * sizeof(char *));
            if (!new_words) {
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(copy);
                return NULL;
            }
            words = new_words;
            capacity = new_capacity;
        }
        words[word_count] = strdup(token);
        if (!words[word_count]) {
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            free(copy);
            return NULL;
        }
        word_count++;
    }
    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(copy);
    return NULL;
}

int main() {
    char test0[] = "a b a c";
    char *r0 = find_first_repeated_word(test0);
    if (r0) {
        printf("%s\n", r0);
        free(r0);
    } else {
        printf("None\n");
    }

    char test1[] = "a b c";
    char *r1 = find_first_repeated_word(test1);
    if (r1) {
        printf("%s\n", r1);
        free(r1);
    } else {
        printf("None\n");
    }

    char test2[] = "cat bat cat";
    char *r2 = find_first_repeated_word(test2);
    if (r2) {
        printf("%s\n", r2);
        free(r2);
    } else {
        printf("None\n");
    }

    return 0;
}