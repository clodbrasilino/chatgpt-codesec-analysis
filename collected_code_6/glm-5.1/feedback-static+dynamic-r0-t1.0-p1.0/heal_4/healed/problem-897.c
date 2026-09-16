#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int word_is_present(const char *sentence, const char *word) {
    const char *p = sentence;
    size_t word_len;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = strlen(word);

    if (word_len == 0) {
        return 0;
    }

    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }

        if (!*p) {
            break;
        }

        const char *word_start = p;
        while (*p && isalpha((unsigned char)*p)) {
            p++;
        }

        if ((size_t)(p - word_start) == word_len) {
            if (strncmp(word_start, word, word_len) == 0) {
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"sentence\" \"word\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("%s\n", word_is_present(argv[1], argv[2]) ? "True" : "False");

    return EXIT_SUCCESS;
}