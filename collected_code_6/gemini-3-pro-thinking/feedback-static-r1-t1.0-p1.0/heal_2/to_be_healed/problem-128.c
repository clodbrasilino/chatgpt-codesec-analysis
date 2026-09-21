#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 4096

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count);
void free_shortlist(char **list, size_t count);

static size_t get_safe_len(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count) {
    if (!words || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (words[i] && get_safe_len(words[i], n + 1) > n) {
            count++;
        }
    }

    *out_count = count;
    if (count == 0) {
        return NULL;
    }

    char **result = calloc(count, sizeof(char *));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (words[i]) {
            size_t len = get_safe_len(words[i], MAX_WORD_LEN);
            if (len > n) {
                result[index] = malloc(len + 1);
                if (!result[index]) {
                    for (size_t j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result[index], words[i], len);
                result[index][len] = '\0';
                index++;
            }
        }
    }

    return result;
}

void free_shortlist(char **list, size_t count) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *word_list[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "fox"
    };
    
    size_t num_words = sizeof(word_list) / sizeof(word_list[0]);
    size_t threshold = 4;
    size_t out_count = 0;

    char **shortlisted = shortlist_words(word_list, num_words, threshold, &out_count);

    if (shortlisted) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free_shortlist(shortlisted, out_count);
    }

    return 0;
}