#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int last_a = ta->elements[ta->size - 1];
    int last_b = tb->elements[tb->size - 1];
    
    if (last_a < last_b) return -1;
    if (last_a > last_b) return 1;
    return 0;
}

void sort_tuples_by_last(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0) return;
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void)
{
    Tuple tuples[5];
    int data0[] = {2, 5};
    int data1[] = {1, 2};
    int data2[] = {4, 4};
    int data3[] = {2, 3};
    int data4[] = {2, 1};
    
    tuples[0].elements = data0;
    tuples[0].size = 2;
    tuples[1].elements = data1;
    tuples[1].size = 2;
    tuples[2].elements = data2;
    tuples[2].size = 2;
    tuples[3].elements = data3;
    tuples[3].size = 2;
    tuples[4].elements = data4;
    tuples[4].size = 2;
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    sort_tuples_by_last(tuples, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("(");
        for (size_t j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j < tuples[i].size - 1) printf(", ");
        }
        printf(")");
        if (i < count - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}