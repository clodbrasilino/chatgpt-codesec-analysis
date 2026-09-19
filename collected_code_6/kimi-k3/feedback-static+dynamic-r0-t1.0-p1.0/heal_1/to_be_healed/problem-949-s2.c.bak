#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static int count_digits(int num)
{
    int digits = 0;
    long n = num;
    
    if (n < 0) {
        n = -n;
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
        total += count_digits(t->elements[i]);
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
    
    int data0[] = {123, 45};
    int data1[] = {7, 8, 9};
    int data2[] = {1000, 200};
    int data3[] = {5};
    
    /* Possible weaknesses found:
     *  Variable 'counts' can be declared as const array [constVariable]
     */
    size_t counts[] = {2, 3, 2, 1};
    /* Possible weaknesses found:
     *  Variable 'datas' can be declared as const array [constVariable]
     */
    int *datas[] = {data0, data1, data2, data3};
    
    for (i = 0; i < num_tuples; i++) {
        tuples[i].count = counts[i];
        tuples[i].elements = (int *)malloc(counts[i] * sizeof(int));
        if (tuples[i].elements == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuples(tuples, num_tuples);
            return EXIT_FAILURE;
        }
        memcpy(tuples[i].elements, datas[i], counts[i] * sizeof(int));
    }
    
    printf("Before sorting: ");
    print_tuples(tuples, num_tuples);
    
    sort_tuples_by_digits(tuples, num_tuples);
    
    printf("After sorting: ");
    print_tuples(tuples, num_tuples);
    
    free_tuples(tuples, num_tuples);
    
    return result;
}