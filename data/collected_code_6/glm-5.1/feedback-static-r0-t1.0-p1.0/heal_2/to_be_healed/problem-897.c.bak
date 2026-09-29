#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int word_is_present(const char *sentence, const char *word) {
    size_t sentence_len;
    size_t word_len;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    sentence_len = strlen(sentence);
    word_len = strlen(word);

    if (word_len == 0 || sentence_len < word_len) {
        return 0;
    }

    size_t i = 0;
    while (i <= sentence_len - word_len) {
        while (i < sentence_len && isspace((unsigned char)sentence[i])) {
            i++;
        }

        if (!isalpha((unsigned char)sentence[i])) {
            if (i < sentence_len) {
                i++;
            }
            continue;
        }

        size_t start = i;
        while (i < sentence_len && isalpha((unsigned char)sentence[i])) {
            i++;
        }
        size_t end = i;

        if (end - start == word_len) {
            if (strncmp(sentence + start, word, word_len) == 0) {
                return 1;
            }
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"sentence\" \"word\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = word_is_present(argv[1], argv[2]);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}