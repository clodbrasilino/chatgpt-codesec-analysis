#include <stdio.h>
#include <stdbool.h>

bool has_increasing_trend(const int *sequence, int length) {
    if (sequence == NULL || length < 2) {
        return false;
    }
    
    for (int i = 1; i < length; i++) {
        if (sequence[i] <= sequence[i - 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const int seq1[] = {1, 2, 3, 4, 5};
    const int seq2[] = {1, 3, 2, 4, 5};
    const int seq3[] = {5, 4, 3, 2, 1};
    const int seq4[] = {1};
    const int seq5[] = {1, 2, 2, 4, 5};
    
    printf("Sequence 1: %s\n", has_increasing_trend(seq1, 5) ? "increasing" : "not increasing");
    printf("Sequence 2: %s\n", has_increasing_trend(seq2, 5) ? "increasing" : "not increasing");
    printf("Sequence 3: %s\n", has_increasing_trend(seq3, 5) ? "increasing" : "not increasing");
    printf("Sequence 4: %s\n", has_increasing_trend(seq4, 1) ? "increasing" : "not increasing");
    printf("Sequence 5: %s\n", has_increasing_trend(seq5, 5) ? "increasing" : "not increasing");
    /* Possible weaknesses found:
     *  Condition 'has_increasing_trend(NULL,5)' is always false
     *  Calling function 'has_increasing_trend' returns 0
     *  Condition 'has_increasing_trend(NULL,5)' is always false [knownConditionTrueFalse]
     */
    printf("Null pointer: %s\n", has_increasing_trend(NULL, 5) ? "increasing" : "not increasing");
    
    return 0;
}