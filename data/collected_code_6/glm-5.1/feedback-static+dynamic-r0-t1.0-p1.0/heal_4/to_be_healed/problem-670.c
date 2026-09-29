#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected True, got 0
  */

int has_decreasing_trend(const int *seq, size_t len) {
    if (seq == NULL || len <= 1) {
        return 0;
    }
    for (size_t i = 1; i < len; ++i) {
        if (seq[i] >= seq[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'seq1' can be declared as const array [constVariable]
     */
    int seq1[] = {5, 4, 3, 2, 1};
    if (has_decreasing_trend(seq1, 5) == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    /* Possible weaknesses found:
     *  Variable 'seq2' can be declared as const array [constVariable]
     */
    int seq2[] = {4, 3, 2, 1};
    if (has_decreasing_trend(seq2, 4) == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    /* Possible weaknesses found:
     *  Variable 'seq3' can be declared as const array [constVariable]
     */
    int seq3[] = {1, 2, 3, 4, 5};
    if (has_decreasing_trend(seq3, 5) == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}