#include <stdio.h>
#include <string.h>

#define WORD_COUNT 8

static int find_two_p_words(const char *const words[], size_t count,
                            const char **first, const char **second)
{
    if (words == NULL || first == NULL || second == NULL) {
        return 0;
    }

    *first = NULL;
    *second = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (words[i] == NULL || words[i][0] != 'p') {
            continue;
        }

        if (*first == NULL) {
            *first = words[i];
        } else if (strcmp(*first, words[i]) != 0) {
            *second = words[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *const words[WORD_COUNT] = {
        "apple",
        "pear",
        "banana",
        "peach",
        "plum",
        "orange",
        "papaya",
        "grape"
    };
    const char *first = NULL;
    const char *second = NULL;

    if (!find_two_p_words(words, WORD_COUNT, &first, &second)) {
        if (fputs("Two distinct words starting with 'p' were not found.\n",
                  stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("%s %s\n", first, second) < 0) {
        return 1;
    }

    return 0;
}