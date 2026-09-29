#include <stdio.h>
#include <string.h>

#define WORD_COUNT 8

int find_two_words_starting_with_p(const char *const words[], size_t count,
                                   const char **first, const char **second)
{
    if (words == NULL || first == NULL || second == NULL) {
        return 0;
    }

    *first = NULL;
    *second = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (words[i] == NULL) {
            continue;
        }

        if (words[i][0] == 'p' || words[i][0] == 'P') {
            if (*first == NULL) {
                *first = words[i];
            } else {
                *second = words[i];
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const char *words[WORD_COUNT] = {
        "apple", "pear", "banana", "plum",
        "orange", "peach", "grape", "melon"
    };
    const char *first = NULL;
    const char *second = NULL;

    if (!find_two_words_starting_with_p(words, WORD_COUNT, &first, &second)) {
        if (fputs("Fewer than two matching words were found.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("%s\n%s\n", first, second) < 0) {
        return 1;
    }

    return 0;
}