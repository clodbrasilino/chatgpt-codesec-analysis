#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_linear(int *sequence, size_t length) {
    if (sequence == NULL || length < 2) {
        return false;
    }

    int diff = sequence[1] - sequence[0];

    for (size_t i = 1; i < length - 1; i++) {
        if (sequence[i + 1] - sequence[i] != diff) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int seq1[] = {1, 3, 5, 7, 9};
    size_t len1 = sizeof(seq1) / sizeof(seq1[0]);
    
    int seq2[] = {1, 3, 6, 7, 9};
    size_t len2 = sizeof(seq2) / sizeof(seq2[0]);

    if (is_linear(seq1, len1)) {
        printf("seq1 is linear\n");
    } else {
        printf("seq1 is not linear\n");
    }

    if (is_linear(seq2, len2)) {
        printf("seq2 is linear\n");
    } else {
        printf("seq2 is not linear\n");
    }

    return 0;
}