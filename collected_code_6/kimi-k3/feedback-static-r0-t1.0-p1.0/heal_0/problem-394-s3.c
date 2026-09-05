#include <stdio.h>
#include <stdlib.h>

int is_distinct(int *tuple, int size) {
    int i, j;
    
    if (tuple == NULL || size <= 0) {
        return 0;
    }
    
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return 0;
            }
        }
    }
    
    return 1;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {1, 2, 3, 2, 5};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    
    printf("Tuple1 is distinct: %d\n", is_distinct(tuple1, size1));
    printf("Tuple2 is distinct: %d\n", is_distinct(tuple2, size2));
    
    return 0;
}