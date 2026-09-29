#include <stdio.h>
#include <string.h>
#include <stddef.h>

int match_p_words(const char *const words[], size_t count,
                  size_t *first_index, size_t *second_index)
{
    size_t i;
    size_t j;

    if (words == NULL || first_index == NULL || second_index == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL || words[i][0] != 'p') {
            continue;
        }
        for (j = i + 1; j < count; j++) {
            if (words[j] == NULL || words[j][0] != 'p') {
                continue;
            }
            if (strcmp(words[i], words[j]) == 0) {
                *first_index = i;
                *second_index = j;
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    const char *const words[] = {
        "apple",
        "pear",
        "peach",
        "plum",
        "banana",
        "pear",
        "grape",
        "peach"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t first = 0;
    size_t second = 0;

    if (match_p_words(words, count, &first, &second) == 1) {
        if (printf("Matched words: \"%s\" (index %zu) and \"%s\" (index %zu)\n",
                   words[first], first, words[second], second) < 0) {
            return 1;
        }
    } else {
        if (printf("No matching words starting with 'p' were found.\n") < 0) {
            return 1;
        }
    }

    return 0;
}