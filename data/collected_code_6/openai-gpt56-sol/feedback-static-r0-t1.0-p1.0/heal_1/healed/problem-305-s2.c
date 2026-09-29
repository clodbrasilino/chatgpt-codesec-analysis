#include <stdio.h>
#include <string.h>

static int find_two_p_words(const char *const *words, size_t count,
                            const char **first, const char **second)
{
    if (words == NULL || first == NULL || second == NULL) {
        return 0;
    }

    *first = NULL;
    *second = NULL;

    for (size_t i = 0; i < count; ++i) {
        const char *word = words[i];

        if (word == NULL || word[0] != 'p') {
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
        "peach",
        "plum",
        "orange",
        "papaya",
        "grape"
    };
    const size_t word_count = sizeof words / sizeof words[0];
    const char *first = NULL;
    const char *second = NULL;

    if (!find_two_p_words(words, word_count, &first, &second)) {
        return fputs("Two distinct words starting with 'p' were not found.\n",
                     stderr) == EOF ? 1 : 1;
    }

    if (printf("%s %s\n", first, second) < 0) {
        return 1;
    }

    return 0;
}