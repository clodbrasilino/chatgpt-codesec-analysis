#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void find_adverbs(const char *sentence) {
    if (sentence == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
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
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(word, sentence + start, word_len);
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