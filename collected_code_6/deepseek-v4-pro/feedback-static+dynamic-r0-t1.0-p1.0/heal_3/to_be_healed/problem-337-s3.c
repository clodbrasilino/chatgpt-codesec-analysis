#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len == 0 || word_len > str_len) {
        return 0;
    }

    size_t pos = str_len - word_len;

    for (size_t i = 0; i < word_len; i++) {
        if (str[pos + i] != word[i]) {
            return 0;
        }
    }

    if (pos > 0) {
        char prev = str[pos - 1];
        if (isalnum((unsigned char)prev) || prev == '_') {
            return 0;
        }
    }

    size_t end = str_len;
    while (end > pos + word_len) {
        char c = str[end - 1];
        if (!ispunct((unsigned char)c)) {
            break;
        }
        end--;
    }

    if (end == pos + word_len) {
        return 1;
    }

    if (end == str_len) {
        return 1;
    }

    return 0;
}

int main(void) {
    printf("%d\n", match_word_at_end("Hello, world", "world"));
    printf("%d\n", match_word_at_end("Hello, world!", "world"));
    printf("%d\n", match_word_at_end("Hello, world!!!", "world"));
    printf("%d\n", match_word_at_end("Hello, worldly", "world"));
    printf("%d\n", match_word_at_end("Hello, underworld", "world"));
    printf("%d\n", match_word_at_end("Hello, World", "world"));
    printf("%d\n", match_word_at_end("world", "world"));
    printf("%d\n", match_word_at_end("world!", "world"));
    printf("%d\n", match_word_at_end("", "world"));
    printf("%d\n", match_word_at_end("Hello", ""));

    return 0;
}