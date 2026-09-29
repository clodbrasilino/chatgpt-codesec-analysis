#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void find_adverbs(const char *sentence) {
    if (sentence == NULL) {
        return;
    }

    size_t i = 0;

    while (sentence[i] != '\0') {
        while (sentence[i] != '\0' && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (sentence[i] == '\0') {
            break;
        }

        size_t start = i;
        while (sentence[i] != '\0' && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        size_t word_len = i - start;

        if (word_len >= 2) {
            char second_to_last = (char)tolower((unsigned char)sentence[i - 2]);
            char last = (char)tolower((unsigned char)sentence[i - 1]);

            if (second_to_last == 'l' && last == 'y') {
                char *word = (char *)malloc(word_len + 1);
                if (word != NULL) {
                    for (size_t j = 0; j < word_len; j++) {
                        word[j] = sentence[start + j];
                    }
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