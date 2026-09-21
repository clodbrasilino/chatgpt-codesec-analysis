#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_repeated_word(const char *str) {
    char *none_str = malloc(5);
    if (none_str) {
        none_str[0] = 'N';
        none_str[1] = 'o';
        none_str[2] = 'n';
        none_str[3] = 'e';
        none_str[4] = '\0';
    }

    if (!str) {
        return none_str;
    }

    size_t capacity = 16;
    char **seen_words = malloc(sizeof(char *) * capacity);
    if (!seen_words) {
        return none_str;
    }

    size_t seen_count = 0;
    char *result = NULL;
    const char *ptr = str;

    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) {
            ptr++;
        }
        if (!*ptr) {
            break;
        }

        const char *start = ptr;
        while (*ptr && !isspace((unsigned char)*ptr)) {
            ptr++;
        }
        size_t word_len = (size_t)(ptr - start);

        char *current_word = malloc(word_len + 1);
        if (!current_word) {
            for (size_t i = 0; i < seen_count; i++) {
                free(seen_words[i]);
            }
            free(seen_words);
            return none_str;
        }

        for (size_t i = 0; i < word_len; i++) {
            current_word[i] = start[i];
        }
        current_word[word_len] = '\0';

        int found = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_words[i], current_word) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            result = current_word;
            break;
        } else {
            if (seen_count >= capacity) {
                size_t new_capacity = capacity * 2;
                char **new_seen = realloc(seen_words, sizeof(char *) * new_capacity);
                if (!new_seen) {
                    free(current_word);
                    for (size_t i = 0; i < seen_count; i++) {
                        free(seen_words[i]);
                    }
                    free(seen_words);
                    return none_str;
                }
                seen_words = new_seen;
                capacity = new_capacity;
            }
            seen_words[seen_count++] = current_word;
        }
    }

    for (size_t i = 0; i < seen_count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);

    if (result) {
        free(none_str);
        return result;
    }

    return none_str;
}

int main(void) {
    const char *test_str = "this is a test and this is only a test";
    char *repeated = find_first_repeated_word(test_str);

    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    }

    const char *test_str2 = "no repeating words here";
    char *repeated2 = find_first_repeated_word(test_str2);

    if (repeated2) {
        printf("%s\n", repeated2);
        free(repeated2);
    }

    return 0;
}