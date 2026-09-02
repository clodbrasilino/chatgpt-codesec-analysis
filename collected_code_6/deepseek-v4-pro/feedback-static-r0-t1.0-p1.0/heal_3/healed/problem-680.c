#include <stdio.h>
#include <stdbool.h>

bool has_increasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL || length < 2) {
        return false;
    }
    
    for (size_t i = 1; i < length; i++) {
        if (sequence[i] <= sequence[i - 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const int seq1[] = {1, 2, 3, 4, 5};
    const int seq2[] = {1, 2, 2, 4, 5};
    const int seq3[] = {5, 4, 3, 2, 1};
    const int seq4[] = {10};
    const int seq5[] = {-3, -1, 0, 2, 7};
    
    printf("seq1: %s\n", has_increasing_trend(seq1, 5) ? "increasing" : "not increasing");
    printf("seq2: %s\n", has_increasing_trend(seq2, 5) ? "increasing" : "not increasing");
    printf("seq3: %s\n", has_increasing_trend(seq3, 5) ? "increasing" : "not increasing");
    printf("seq4: %s\n", has_increasing_trend(seq4, 1) ? "increasing" : "not increasing");
    printf("seq5: %s\n", has_increasing_trend(seq5, 5) ? "increasing" : "not increasing");
    
    const int *null_seq = NULL;
    bool null_result = has_increasing_trend(null_seq, 5);
    printf("null: %s\n", null_result ? "increasing" : "not increasing");
    
    return 0;
}