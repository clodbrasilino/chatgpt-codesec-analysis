#include <stdio.h>

static int find_two_words_starting_with_p(const char *const words[],
                                          size_t count,
                                          const char **first,
                                          const char **second)
{
    if (words == NULL || first == NULL || second == NULL) {
        return 0;
    }

    *first = NULL;
    *second = NULL;

    for (size_t i = 0; i < count; ++i) {
        const char *word = words[i];

        if (word != NULL && (word[0] == 'p' || word[0] == 'P')) {
            if (*first == NULL) {
                *first = word;
            } else {
                *second = word;
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    static const char *const words[] = {
        "apple",
        "pear",
        "banana",
        "plum",
        "orange",
        "peach",
        "grape",
        "melon"
    };
    const size_t word_count = sizeof words / sizeof words[0];
    const char *first = NULL;
    const char *second = NULL;

    if (!find_two_words_starting_with_p(words, word_count, &first, &second)) {
        return fputs("Fewer than two matching words were found.\n", stderr) == EOF
                   ? 1
                   : 1;
    }

    if (printf("%s\n%s\n", first, second) < 0) {
        return 1;
    }

    return 0;
}