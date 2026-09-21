#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 26
#define MAX_WORD_LEN 64

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int extract_words(const char *str, char words[MAX_WORDS][MAX_WORD_LEN], size_t *count)
{
    size_t i = 0;
    size_t w = 0;

    if (str == NULL || words == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    while (str[i] != '\0') {
        while (str[i] == ' ') {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        if (w >= MAX_WORDS) {
            return -1;
        }
        size_t len = 0;
        while (str[i] != '\0' && str[i] != ' ') {
            if (len >= MAX_WORD_LEN - 1) {
                return -1;
            }
            words[w][len] = str[i];
            len++;
            i++;
        }
        words[w][len] = '\0';
        w++;
    }

    *count = w;
    return 0;
}

int follows_pattern(const char *pattern, const char *str)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char mapping[26][MAX_WORD_LEN];
    int mapped[26] = {0};
    size_t word_count = 0;
    size_t pattern_len;
    size_t i;

    if (pattern == NULL || str == NULL) {
        return 0;
    }

    if (extract_words(str, words, &word_count) != 0) {
        return 0;
    }

    pattern_len = strnlen(pattern, MAX_WORDS + 1);

    if (pattern_len > MAX_WORDS || pattern_len != word_count) {
        return 0;
    }

    for (i = 0; i < pattern_len; i++) {
        char c = pattern[i];
        if (c < 'a' || c > 'z') {
            return 0;
        }
        int idx = c - 'a';
        if (mapped[idx]) {
            if (strncmp(mapping[idx], words[i], MAX_WORD_LEN) != 0) {
                return 0;
            }
        } else {
            size_t j;
            for (j = 0; j < 26; j++) {
                if (mapped[j] && strncmp(mapping[j], words[i], MAX_WORD_LEN) == 0) {
                    return 0;
                }
            }
            size_t word_len = strnlen(words[i], MAX_WORD_LEN);
            if (word_len >= MAX_WORD_LEN) {
                return 0;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(mapping[idx], words[i], word_len);
            mapping[idx][word_len] = '\0';
            mapped[idx] = 1;
        }
    }

    return 1;
}

int main(void)
{
    const char *patterns[] = {"abba", "abba", "aaaa", "abba"};
    const char *strings[] = {
        "dog cat cat dog",
        "dog cat cat fish",
        "dog cat cat dog",
        "dog dog dog dog"
    };
    size_t n = sizeof(patterns) / sizeof(patterns[0]);
    size_t i;

    for (i = 0; i < n; i++) {
        int result = follows_pattern(patterns[i], strings[i]);
        if (printf("Pattern \"%s\" with \"%s\": %s\n",
                   patterns[i], strings[i],
                   result ? "true" : "false") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}