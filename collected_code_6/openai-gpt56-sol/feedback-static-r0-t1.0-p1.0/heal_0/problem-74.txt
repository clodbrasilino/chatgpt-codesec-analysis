#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool follows_pattern(const int *sequence, size_t sequence_length,
                            const int *patterns, size_t pattern_length)
{
    size_t i;

    if ((sequence == NULL && sequence_length != 0U) ||
        (patterns == NULL && pattern_length != 0U)) {
        return false;
    }

    if (pattern_length == 0U) {
        return sequence_length == 0U;
    }

    if (sequence_length != pattern_length) {
        return false;
    }

    for (i = 0U; i < pattern_length; ++i) {
        if (sequence[i] != patterns[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int patterns[] = {1, 2, 3, 5, 8};
    const int sequence[] = {1, 2, 3, 5, 8};
    const size_t pattern_length = sizeof patterns / sizeof patterns[0];
    const size_t sequence_length = sizeof sequence / sizeof sequence[0];

    if (follows_pattern(sequence, sequence_length, patterns, pattern_length)) {
        if (puts("The sequence follows the pattern.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The sequence does not follow the pattern.") == EOF) {
            return 1;
        }
    }

    return 0;
}