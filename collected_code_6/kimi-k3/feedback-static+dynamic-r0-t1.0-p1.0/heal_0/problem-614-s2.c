#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

long long cumulative_sum(const Tuple *tuple_list, size_t list_size) {
    if (tuple_list == NULL) {
        return 0;
    }
    
    long long sum = 0;
    
    for (size_t i = 0; i < list_size; i++) {
        if (tuple_list[i].data == NULL || tuple_list[i].size == 0) {
            continue;
        }
        
        for (size_t j = 0; j < tuple_list[i].size; j++) {
            sum += (long long)tuple_list[i].data[j];
        }
    }
    
    return sum;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};
    
    Tuple tuple_list[] = {
        {data1, sizeof(data1) / sizeof(data1[0])},
        {data2, sizeof(data2) / sizeof(data2[0])},
        {data3, sizeof(data3) / sizeof(data3[0])}
    };
    
    size_t list_size = sizeof(tuple_list) / sizeof(tuple_list[0]);
    
    long long result = cumulative_sum(tuple_list, list_size);
    
    printf("Cumulative sum: %lld\n", result);
    
    return EXIT_SUCCESS;
}