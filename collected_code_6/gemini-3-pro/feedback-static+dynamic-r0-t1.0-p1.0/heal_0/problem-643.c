#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_z_inside_word(const char *word) {
    if (word == NULL) {
        return 0;
    }

    size_t len = strlen(word);

    if (len < 3) {
        return 0;
    }

    if (tolower((unsigned char)word[0]) == 'z' || tolower((unsigned char)word[len - 1]) == 'z') {
        return 0;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (tolower((unsigned char)word[i]) == 'z') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_words[] = {
        "pizza",
        "zebra",
        "buzz",
        "amazing",
        "apple",
        "z",
        "sz",
        "zs",
        NULL
    };

    for (size_t i = 0; test_words[i] != NULL; i++) {
        int result = match_z_inside_word(test_words[i]);
        if (result) {
            printf("Matched: %s\n", test_words[i]);
        } else {
            printf("Not Matched: %s\n", test_words[i]);
        }
    }

    return 0;
}