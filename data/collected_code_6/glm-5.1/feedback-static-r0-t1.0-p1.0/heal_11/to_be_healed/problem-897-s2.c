#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        return false;
    }

    const char *p = sentence;

    while (*p) {
        while (*p && strchr(" \t\n\r.,!?;:\"'", *p)) {
            p++;
        }

        if (!*p) {
            break;
        }

        const char *word_start = p;

        while (*p && !strchr(" \t\n\r.,!?;:\"'", *p)) {
            p++;
        }

        size_t token_len = p - word_start;

        if (token_len == word_len && strncmp(word_start, word, word_len) == 0) {
            return true;
        }
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"<sentence>\" \"<word>\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_word_present(argv[1], argv[2])) {
        printf("Word is present.\n");
    } else {
        printf("Word is not present.\n");
    }

    return EXIT_SUCCESS;
}