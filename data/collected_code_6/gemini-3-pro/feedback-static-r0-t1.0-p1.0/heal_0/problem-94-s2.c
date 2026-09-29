#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Tuple;

Tuple extract_min_value_record(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        Tuple empty = {-1, -1};
        return empty;
    }

    Tuple min_tuple = tuples[0];
    
    for (size_t i = 1; i < size; ++i) {
        if (tuples[i].value < min_tuple.value) {
            min_tuple = tuples[i];
        }
    }
    
    return min_tuple;
}

int main(void) {
    Tuple tuples[] = {
        {0, 45},
        {1, 23},
        {2, 89},
        {3, 12},
        {4, 67}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    
    Tuple min_record = extract_min_value_record(tuples, size);
    
    if (min_record.index != -1) {
        printf("Min value record - Index: %d, Value: %d\n", min_record.index, min_record.value);
    } else {
        printf("Invalid input or empty array.\n");
    }
    
    return 0;
}