#include <stdio.h>
#include <stdlib.h>

struct Counter {
    int value;
};

int compare_value(const void* a, const void* b) {
    return (((struct Counter*)a)->value - ((struct Counter*)b)->value);
}

void sort_counter_by_value(struct Counter* counter, size_t length) {
    qsort(counter, length, sizeof(struct Counter), compare_value);
}

int main() {
    struct Counter counter[5] = { {5}, {1}, {3}, {2}, {4} };
    
    printf("Before Sorting: \n");
    for(int i = 0; i<5; i++) {
        printf("%d ", counter[i].value);
    }
    
    sort_counter_by_value(counter, 5);
    
    printf("\nAfter Sorting: \n");
    for(int i = 0; i<5; i++) {
        printf("%d ", counter[i].value);
    }

    return 0;
}