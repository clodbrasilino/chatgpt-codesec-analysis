#if defined(__linux__) || defined(__APPLE__) || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCE_LEN 1048576

void find_adverbs(const char *sentence) {
    if (sentence == NULL) {
        return;
    }

    size_t len = strnlen(sentence, MAX_SENTENCE_LEN);
    size_t i = 0;

    while (i < len) {
        while (i < len && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        size_t start = i;
        while (i < len && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        size_t word_len = i - start;

        if (word_len >= 2) {
            char second_to_last = (char)tolower((unsigned char)sentence[i - 2]);
            char last = (char)tolower((unsigned char)sentence[i - 1]);

            if (second_to_last == 'l' && last == 'y') {
                char *word = (char *)malloc(word_len + 1);
                if (word != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(word, sentence + start, word_len);
                    word[word_len] = '\0';
                    printf("Adverb: '%s', Position: %zu\n", word, start);
                    free(word);
                }
            }
        }
    }
}

int main(void) {
    const char *text = "The cat silently stalked its prey, moving very quickly and carefully.";
    
    printf("Text: %s\n", text);
    find_adverbs(text);
    
    return 0;
}