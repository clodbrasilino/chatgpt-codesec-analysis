#include <stdio.h>
#include <stdlib.h>

int max_occuring_divisor(int start, int end, int *max_divisor) {
    if (start > end || start < 1 || max_divisor == NULL) {
        return -1;
    }
    
    int range_size = end - start + 1;
    int *divisor_count = (int *)calloc((size_t)(end + 1), sizeof(int));
    if (divisor_count == NULL) {
        return -1;
    }
    
    for (int i = start; i <= end; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                divisor_count[j]++;
                if (j != i / j) {
                    divisor_count[i / j]++;
                }
            }
        }
    }
    
    int max_count = 0;
    int result = 1;
    
    for (int i = 1; i <= end; i++) {
        if (divisor_count[i] > max_count) {
            max_count = divisor_count[i];
            result = i;
        }
    }
    
    free(divisor_count);
    divisor_count = NULL;
    
    *max_divisor = result;
    return 0;
}

int main(void) {
    int start, end, max_divisor;
    
    if (scanf("%d %d", &start, &end) != 2) {
        return EXIT_FAILURE;
    }
    
    if (max_occuring_divisor(start, end, &max_divisor) != 0) {
        return EXIT_FAILURE;
    }
    
    printf("%d\n", max_divisor);
    
    return EXIT_SUCCESS;
}