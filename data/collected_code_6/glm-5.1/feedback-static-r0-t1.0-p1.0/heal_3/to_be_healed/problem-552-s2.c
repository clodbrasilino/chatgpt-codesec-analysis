#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_linear(const int *sequence, size_t length) {
    if (sequence == NULL) {
        return false;
    }

    if (length <= 2) {
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
    int seq1[] = {1, 2, 3, 4, 5};
    int seq2[] = {2, 4, 8, 16};
    int seq3[] = {10};
    int seq4[] = {5, 5, 5, 5};
    int seq5[] = {};
    /* Possible weaknesses found:
     *  Variable 'seq6' can be declared as pointer to const [constVariablePointer]
     */
    int *const seq6 = NULL;

    printf("%d\n", is_linear(seq1, sizeof(seq1) / sizeof(seq1[0])));
    printf("%d\n", is_linear(seq2, sizeof(seq2) / sizeof(seq2[0])));
    printf("%d\n", is_linear(seq3, sizeof(seq3) / sizeof(seq3[0])));
    printf("%d\n", is_linear(seq4, sizeof(seq4) / sizeof(seq4[0])));
    printf("%d\n", is_linear(seq5, sizeof(seq5) / sizeof(seq5[0])));
    printf("%d\n", is_linear(seq6, 0));

    return 0;
}