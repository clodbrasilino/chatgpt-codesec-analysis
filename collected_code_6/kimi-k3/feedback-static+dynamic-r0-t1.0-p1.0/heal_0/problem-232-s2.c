#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_ints_desc(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

int *get_n_largest(const int *data, size_t count, size_t n)
{
    if (data == NULL || count == 0 || n == 0) {
        return NULL;
    }
    
    if (n > count) {
        n = count;
    }
    
    int *result = malloc(n * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    
    int *temp = malloc(count * sizeof(*temp));
    if (temp == NULL) {
        free(result);
        return NULL;
    }
    
    memcpy(temp, data, count * sizeof(*temp));
    qsort(temp, count, sizeof(*temp), compare_ints_desc);
    memcpy(result, temp, n * sizeof(*result));
    
    free(temp);
    return result;
}

int main(void)
{
    int dataset[] = {15, 3, 9, 22, 7, 1, 18, 4};
    size_t count = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    
    int *largest = get_n_largest(dataset, count, n);
    if (largest == NULL) {
        fprintf(stderr, "Error: failed to get largest items\n");
        return EXIT_FAILURE;
    }
    
    printf("Top %zu largest items: ", n);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", largest[i]);
    }
    printf("\n");
    
    free(largest);
    return EXIT_SUCCESS;
}