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

    if (sentence[0] == '\0' || word[0] == '\0') {
        return 0;
    }

    sentence_len = 0;
    while (sentence[sentence_len] != '\0') {
        sentence_len++;
    }

    word_len = 0;
    while (word[word_len] != '\0') {
        if ((size_t)-1 - word_len == 0) {
            break;
        }
        word_len++;
    }

    if (word_len == 0 || sentence_len < word_len) {
        return 0;
    }

    size_t i = 0;
    while (i <= sentence_len - word_len) {
        while (i < sentence_len && isspace((unsigned char)sentence[i])) {
            i++;
        }

        if (i < sentence_len && !isalpha((unsigned char)sentence[i])) {
            i++;
            continue;
        }

        size_t start = i;
        while (i < sentence_len && isalpha((unsigned char)sentence[i])) {
            i++;
        }
        size_t end = i;

        if (end - start == word_len) {
            size_t j;
            int match = 1;
            for (j = 0; j < word_len; j++) {
                if (sentence[start + j] != word[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"sentence\" \"word\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = word_is_present(argv[1], argv[2]);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}