#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_linear(const int *sequence, size_t length) {
    if (sequence == NULL || length < 2) {
        return true;
    }

    int diff = sequence[1] - sequence[0];

    for (size_t i = 2; i < length; i++) {
        if (sequence[i] - sequence[i - 1] != diff) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int seq1[] = {2, 4, 6, 8, 10};
    size_t len1 = sizeof(seq1) / sizeof(seq1[0]);
    if (is_linear(seq1, len1)) {
        printf("Sequence 1 is linear.\n");
    } else {
        printf("Sequence 1 is not linear.\n");
    }

    int seq2[] = {2, 4, 7, 8, 10};
    size_t len2 = sizeof(seq2) / sizeof(seq2[0]);
    if (is_linear(seq2, len2)) {
        printf("Sequence 2 is linear.\n");
    } else {
        printf("Sequence 2 is not linear.\n");
    }

    return 0;
}