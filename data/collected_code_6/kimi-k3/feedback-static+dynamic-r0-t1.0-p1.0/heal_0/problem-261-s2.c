#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

int divide_tuples(const Tuple *dividend, const Tuple *divisor, Tuple **result)
{
    if (dividend == NULL || divisor == NULL || result == NULL) {
        return EINVAL;
    }
    
    if (dividend->count != divisor->count) {
        return EINVAL;
    }
    
    if (dividend->count == 0) {
        *result = NULL;
        return 0;
    }
    
    if (dividend->count > SIZE_MAX / sizeof(int)) {
        return EOVERFLOW;
    }
    
    Tuple *res = malloc(sizeof(Tuple));
    if (res == NULL) {
        return ENOMEM;
    }
    
    res->elements = malloc(dividend->count * sizeof(int));
    if (res->elements == NULL) {
        free(res);
        return ENOMEM;
    }
    
    res->count = dividend->count;
    
    for (size_t i = 0; i < dividend->count; i++) {
        if (divisor->elements[i] == 0) {
            free(res->elements);
            free(res);
            return EDOM;
        }
        res->elements[i] = dividend->elements[i] / divisor->elements[i];
    }
    
    *result = res;
    return 0;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void)
{
    int arr1[] = {10, 20, 30, 40, 50};
    int arr2[] = {2, 4, 5, 8, 10};
    
    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};
    Tuple *result = NULL;
    
    int err = divide_tuples(&t1, &t2, &result);
    if (err != 0) {
        fprintf(stderr, "Error: %d\n", err);
        return EXIT_FAILURE;
    }
    
    if (result != NULL) {
        for (size_t i = 0; i < result->count; i++) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
        free_tuple(result);
    }
    
    return EXIT_SUCCESS;
}