#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int key;
    int value;
} counter;

int compare_count(const void * a, const void * b) {
    return ( ((counter*)b)->value - ((counter*)a)->value );
}

void sort_counter(counter* counters, int size) {
    if(counters != NULL && size > 0) {
        qsort(counters, size, sizeof(counter), compare_count);
    }
}

int main() {
    counter counts[] = {{1, 20}, {2, 10}, {3, 60}, {4, 30}, {5, 50}};
    int size = sizeof(counts) / sizeof(counts[0]);

    sort_counter(counts, size);
    
    for(int i = 0; i < size; i++) {
        printf("Key: %d - Value: %d\n", counts[i].key, counts[i].value);
    }
    return 0;
}