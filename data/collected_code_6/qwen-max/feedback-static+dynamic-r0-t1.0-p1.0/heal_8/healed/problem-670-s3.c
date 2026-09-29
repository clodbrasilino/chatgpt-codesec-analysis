#include <stdio.h>
#include <stdbool.h>

bool is_decreasing_trend(const int *sequence, int length) {
    for (int i = 1; i < length; ++i) {
        if (sequence[i - 1] <= sequence[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int sequence[] = {5, 4, 3, 2, 1};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    const char *result = is_decreasing_trend(sequence, length) ? "The sequence is in a decreasing trend.\n" : "The sequence is not in a decreasing trend.\n";
    printf(result);

    int sequence2[] = {5, 4, 3, 3, 1};
    length = sizeof(sequence2) / sizeof(sequence2[0]);
    result = is_decreasing_trend(sequence2, length) ? "The sequence is in a decreasing trend.\n" : "The sequence is not in a decreasing trend.\n";
    printf(result);

    int sequence3[] = {5, 6, 3, 2, 1};
    length = sizeof(sequence3) / sizeof(sequence3[0]);
    result = is_decreasing_trend(sequence3, length) ? "The sequence is in a decreasing trend.\n" : "The sequence is not in a decreasing trend.\n";
    printf(result);

    return 0;
}