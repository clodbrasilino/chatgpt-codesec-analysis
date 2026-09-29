#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool follows_pattern(const int sequence[], size_t sequence_length,
                            const int patterns[], size_t pattern_length)
{
    size_t i;
    size_t pattern_index = 0U;

    if ((sequence_length > 0U && sequence == NULL) ||
        (pattern_length > 0U && patterns == NULL)) {
        return false;
    }

    if (pattern_length == 0U) {
        return true;
    }

    for (i = 0U; i < sequence_length; ++i) {
        if (sequence[i] == patterns[pattern_index]) {
            ++pattern_index;
            if (pattern_index == pattern_length) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    const int sequence[] = {5, 1, 3, 2, 4, 8};
    const int patterns[] = {1, 2, 8};
    const size_t sequence_length = sizeof(sequence) / sizeof(sequence[0]);
    const size_t pattern_length = sizeof(patterns) / sizeof(patterns[0]);
    const bool result = follows_pattern(sequence, sequence_length,
                                        patterns, pattern_length);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}