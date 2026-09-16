#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

bool has_decreasing_trend(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return false;
    }
    
    for (size_t i = 1; i < size; i++) {
        if (arr[i] >= arr[i - 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int seq1[] = {9, 7, 5, 3, 1};
    int seq2[] = {9, 7, 8, 3, 1};
    int seq3[] = {5};
    int seq4[] = {5, 5, 5, 5};
    int seq5[] = {1, 3, 5, 7, 9};
    int seq6[] = {10, 8, 6, 4, 2};
    
    printf("seq1: %s\n", has_decreasing_trend(seq1, sizeof(seq1)/sizeof(seq1[0])) ? "True" : "False");
    printf("seq2: %s\n", has_decreasing_trend(seq2, sizeof(seq2)/sizeof(seq2[0])) ? "True" : "False");
    printf("seq3: %s\n", has_decreasing_trend(seq3, sizeof(seq3)/sizeof(seq3[0])) ? "True" : "False");
    printf("seq4: %s\n", has_decreasing_trend(seq4, sizeof(seq4)/sizeof(seq4[0])) ? "True" : "False");
    printf("seq5: %s\n", has_decreasing_trend(seq5, sizeof(seq5)/sizeof(seq5[0])) ? "True" : "False");
    printf("seq6: %s\n", has_decreasing_trend(seq6, sizeof(seq6)/sizeof(seq6[0])) ? "True" : "False");
    
    return 0;
}