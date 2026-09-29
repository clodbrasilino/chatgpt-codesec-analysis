#include <stdio.h>
#include <stdlib.h>

static int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Possible weaknesses found:
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 */
long long min_abs_sum_diff(int *a, int *b, int n) {
    if (a == NULL || b == NULL || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    
    int *sorted_a = (int *)malloc((size_t)n * sizeof(int));
    int *sorted_b = (int *)malloc((size_t)n * sizeof(int));
    
    if (sorted_a == NULL || sorted_b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(sorted_a);
        free(sorted_b);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        sorted_a[i] = a[i];
        sorted_b[i] = b[i];
    }
    
    qsort(sorted_a, (size_t)n, sizeof(int), compare);
    qsort(sorted_b, (size_t)n, sizeof(int), compare);
    
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long diff = (long long)sorted_a[i] - sorted_b[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }
    
    free(sorted_a);
    free(sorted_b);
    
    return sum;
}

int main(void) {
    int a[] = {4, 1, 8, 7};
    int b[] = {2, 3, 6, 5};
    int n = (int)(sizeof(a) / sizeof(a[0]));
    
    long long result = min_abs_sum_diff(a, b, n);
    printf("%lld\n", result);
    
    return 0;
}