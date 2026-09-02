#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isLinearSequence(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return false;
    }

    int diff = arr[1] - arr[0];
    for (size_t i = 1; i < size - 1; i++) {
        if (arr[i + 1] - arr[i] != diff) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int seq1[] = {1, 3, 5, 7, 9};
    int seq2[] = {2, 4, 8, 16, 32};
    int seq3[] = {5, 5, 5, 5};
    int seq4[] = {10};
    int seq5[] = {1, 2, 4, 7};

    bool isLinear1 = isLinearSequence(seq1, sizeof(seq1) / sizeof(seq1[0]));
    bool isLinear2 = isLinearSequence(seq2, sizeof(seq2) / sizeof(seq2[0]));
    bool isLinear3 = isLinearSequence(seq3, sizeof(seq3) / sizeof(seq3[0]));
    bool isLinear4 = isLinearSequence(seq4, sizeof(seq4) / sizeof(seq4[0]));
    bool isLinear5 = isLinearSequence(seq5, sizeof(seq5) / sizeof(seq5[0]));
    bool isLinearNull = isLinearSequence(NULL, 0);

    printf("Sequence 1 is %s\n", isLinear1 ? "linear" : "not linear");
    printf("Sequence 2 is %s\n", isLinear2 ? "linear" : "not linear");
    printf("Sequence 3 is %s\n", isLinear3 ? "linear" : "not linear");
    printf("Sequence 4 is %s\n", isLinear4 ? "linear" : "not linear");
    printf("Sequence 5 is %s\n", isLinear5 ? "linear" : "not linear");
    printf("NULL sequence is %s\n", isLinearNull ? "linear" : "not linear");

    return 0;
}