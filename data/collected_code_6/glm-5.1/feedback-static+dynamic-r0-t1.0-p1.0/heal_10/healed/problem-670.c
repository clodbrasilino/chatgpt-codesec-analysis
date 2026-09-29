#include <stdio.h>
#include <stdlib.h>

int has_decreasing_trend(const int *seq, size_t len) {
    if (seq == NULL || len < 2) {
        return 0;
    }
    for (size_t i = 1; i < len; ++i) {
        if (seq[i] < seq[i - 1]) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    const int seq1[] = {5, 4, 3, 2, 1};
    printf("%s\n", has_decreasing_trend(seq1, 5) ? "True" : "False");
    
    const int seq2[] = {4, 3, 2, 1};
    printf("%s\n", has_decreasing_trend(seq2, 4) ? "True" : "False");
    
    const int seq3[] = {1, 2, 3, 4, 5};
    printf("%s\n", has_decreasing_trend(seq3, 5) ? "True" : "False");
    
    return 0;
}