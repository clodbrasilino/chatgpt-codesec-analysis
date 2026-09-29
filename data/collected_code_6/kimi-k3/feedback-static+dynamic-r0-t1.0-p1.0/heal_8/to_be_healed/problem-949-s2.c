#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static int count_digits(int num)
{
    int digits = 0;
    long n = num;
    
    if (n < 0) {
        if (n == LONG_MIN) {
            n = LONG_MAX;
        } else {
            n = -n;
        }
    }
    
    if (n == 0) {
        return 1;
    }
    
    while (n > 0) {
        n /= 10;
        digits++;
    }
    
    return digits;
}

static int total_digits_in_tuple(const Tuple *t)
{
    int total = 0;
    size_t i;
    
    if (t == NULL || t->elements == NULL) {
        return 0;
    }
    
    for (i = 0; i < t->count; i++) {
        int d = count_digits(t->elements[i]);
        if (total > INT_MAX - d) {
            return INT_MAX;
        }
        total += d;
    }
    
    return total;
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int digits_a = total_digits_in_tuple(ta);
    int digits_b = total_digits_in_tuple(tb);
    
    if (digits_a < digits_b) {
        return -1;
    }
    if (digits_a > digits_b) {
        return 1;
    }
    return 0;
}

void sort_tuples_by_digits(Tuple *tuples, size_t num_tuples)
{
    if (tuples == NULL || num_tuples == 0) {
        return;
    }
    
    qsort(tuples, num_tuples, sizeof(Tuple), compare_tuples);
}

static void free_tuples(Tuple *tuples, size_t num_tuples)
{
    size_t i;
    
    if (tuples == NULL) {
        return;
    }
    
    for (i = 0; i < num_tuples; i++) {
        free(tuples[i].elements);
        tuples[i].elements = NULL;
        tuples[i].count = 0;
    }
    free(tuples);
}

static void print_tuples(const Tuple *tuples, size_t num_tuples)
{
    size_t i, j;
    
    if (tuples == NULL) {
        return;
    }
    
    for (i = 0; i < num_tuples; i++) {
        printf("(");
        for (j = 0; j < tuples[i].count; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j < tuples[i].count - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < num_tuples - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

static int safe_copy_int_array(int *dest, size_t dest_size, const int *src, size_t src_count)
{
    size_t required_size;
    
    if (dest == NULL || src == NULL) {
        return -1;
    }
    
    if (src_count == 0) {
        return 0;
    }
    
    if (src_count > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    required_size = src_count * sizeof(int);
    
    /* Possible weaknesses found:
     *  If condition 'dest_size<required_size' is true, the function will return/exit
     */
    if (dest_size < required_size) {
        return -1;
    }
    
    if (dest_size < src_count * sizeof(int)) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Testing identical condition 'dest_size<required_size'
     *  Identical condition 'dest_size<required_size', second condition is always false [identicalConditionAfterEarlyExit]
     */
    if (required_size > dest_size) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, required_size);
    return 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t num_tuples = 4;
    size_t i;
    int result = EXIT_SUCCESS;
    
    tuples = (Tuple *)calloc(num_tuples, sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    const int data0[] = {123, 45};
    const int data1[] = {7, 8, 9};
    const int data2[] = {1000, 200};
    const int data3[] = {5};
    
    const size_t counts[] = {2, 3, 2, 1};
    const int * const datas[] = {data0, data1, data2, data3};
    
    for (i = 0; i < num_tuples; i++) {
        if (counts[i] == 0) {
            continue;
        }
        
        if (counts[i] > SIZE_MAX / sizeof(int)) {
            fprintf(stderr, "Size overflow detected\n");
            free_tuples(tuples, num_tuples);
            return EXIT_FAILURE;
        }
        
        size_t alloc_size = counts[i] * sizeof(int);
        
        tuples[i].count = counts[i];
        tuples[i].elements = (int *)malloc(alloc_size);
        if (tuples[i].elements == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuples(tuples, num_tuples);
            return EXIT_FAILURE;
        }
        
        if (datas[i] != NULL) {
            if (safe_copy_int_array(tuples[i].elements, alloc_size, datas[i], counts[i]) != 0) {
                fprintf(stderr, "Buffer copy failed\n");
                free_tuples(tuples, num_tuples);
                return EXIT_FAILURE;
            }
        }
    }
    
    printf("Before sorting: ");
    print_tuples(tuples, num_tuples);
    
    sort_tuples_by_digits(tuples, num_tuples);
    
    printf("After sorting: ");
    print_tuples(tuples, num_tuples);
    
    free_tuples(tuples, num_tuples);
    
    return result;
}