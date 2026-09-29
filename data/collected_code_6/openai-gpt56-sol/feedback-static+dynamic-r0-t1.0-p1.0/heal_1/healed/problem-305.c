#include <stdio.h>
#include <string.h>

static int find_two_words_starting_with_p(const char *const *words,
                                          size_t count,
                                          const char **first,
                                          const char **second)
{
    if (words == NULL || first == NULL || second == NULL) {
        return -1;
    }

    *first = NULL;
    *second = NULL;

    for (size_t i = 0; i < count; ++i) {
        const char *word = words[i];

        if (word == NULL) {
            continue;
        }

        if (word[0] != 'p' && word[0] != 'P') {
            continue;
        }

        if (*first == NULL) {
            *first = word;
        } else if (strcmp(*first, word) != 0) {
            *second = word;
            return 1;
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

    const char *first = NULL;
    const char *second = NULL;
    const size_t word_count = sizeof words / sizeof words[0];

    int result = find_two_words_starting_with_p(words, word_count,
                                                &first, &second);

    if (result < 0) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (result == 0) {
        if (fputs("Two distinct words starting with 'p' were not found.\n",
                  stdout) == EOF) {
            return 1;
        }
        return 0;
    }

    if (printf("%s %s\n", first, second) < 0) {
        return 1;
    }

    return 0;
}